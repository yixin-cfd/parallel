#include <omp.h>
#include <stdio.h>

// int main() {
//     #pragma omp parallel
//     printf("Hello, OpenMP!\n");
//     return 0;
// }


int main() {
    printf("Hello 1!\n");
    #pragma omp parallel
    {
        printf("Hi\n");
    }
    printf("Hello 2!\n");
    return 0;
}