#include <iostream>
#include <mpi.h>
#include <math.h>
#include <iomanip>
using namespace std;

#define BLOCK_LOW(id, p, n) ((id) * (n) / p)                 // 该进程控制的第一个元素的下标表达式
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1) // 该进程控制的最后一个元素的下标表达式
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1, p, n) - BLOCK_LOW(id, p, n))
#define BLOCK_OWNER(index, p, n) (((p) * ((index) + 1) - 1) / (n)) // 控制该数组元素的进程号

int main(int argc, char *argv[])
{
    int count;            // 局部素数计数
    double elapesed_time; // 并行计算时间
    int first;            // 素数位置局部索引
    int global_count;     // 全局素数计数
    int high_value;
    int i;
    int id;    // 进程号
    int index; // 当前素数索引
    int low_value;
    char *marked;
    int n; // 2, .., n
    int p; // 处理器总数
    int proc0_size;
    int prime; // 当前素数
    int size;
    MPI_Init(&argc, &argv);

    MPI_Barrier(MPI_COMM_WORLD); // 阻塞
    elapesed_time -= MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (argc != 2)
    {
        if (id == 0)
            cerr << "Command line: " << argv[0] << endl;
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    n = stoi(argv[1]);

    low_value = 2 + BLOCK_LOW(id, p, n - 1);
    high_value = 2 + BLOCK_HIGH(id, p, n - 1);
    size = BLOCK_SIZE(id, p, n - 1);

    proc0_size = (n - 1) / p;
    if ((2 + proc0_size) < (int)sqrt((double)n))
    {
        if (id == 0)
            cerr << "Too many process" << endl;
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    marked = (char *)malloc(size);
    if (marked == NULL)
    {
        cerr << "Cannot allocate enough memory" << endl;
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; i++)
        marked[i] = 0;
    if (id == 0)
        index = 0;
    prime = 2;
    do
    {
        if (prime * prime > low_value)
            first = prime * prime - low_value;
        else
        {
            if (!(low_value % prime))
                first = 0;
            else
                first = prime - (low_value % prime);
        }
        for (i = first; i < size; i += prime)
            marked[i] = 1;
        if (id == 0)
        {
            while (marked[++index])
                ;
            prime = index + 2;
        }
        MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);       // 进程0 将自己的prime 广播给其他进程

    } while (prime * prime <= n);
    count = 0;
    for (int i = 0; i < size; i++)
        if (!marked[i])
            count++;
    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    elapesed_time += MPI_Wtime();
    if (id == 0)
    {
        cout << global_count << " primes are less than or equal to " << n << endl;
        cout << "Total elapsed time: " << setw(10) << fixed << setprecision(6) << elapesed_time << endl;
    }

    MPI_Finalize();
    return 0;
}