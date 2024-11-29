#include <iostream>
#include <mpi.h>
using namespace std;

using dtype = int;
#define MPI_TYPE MPI_INT

void terminate_(int id, char*error_messsage){
    if(id == 0){
        cerr << error_messsage << endl;
        cerr.flush();
    }
    MPI_Finalize();
    exit(EXIT_FAILURE);
}

void read_row_striped_matrix(char *s,)


int main(int argc, char *argv[]){
    dtype **a;
    dtype *storage;
    int i, j, k;
    int id;
    int m;
    int n;
    int p;
    void compute_shortest_paths(int, int, int **, int);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p); 
    read_row_striped_matrix(argv[1], (void*)&a, (void *)&storage, MPI_TYPE, &m, &n, MPI_COMM_WORLD);
    if(m != n) terminate_(id, "Matrix must be square\n");
    print_row_striped_matrix((void**)a, MPI_TYPE, m, n, MPI_COMM_WORLD);
    compute_shortest_paths(id, p, (dtype ** )a, n);
    print_row_striped_matrix((void**)a, MPI_TYPE, m, n, MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}