#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char *argv[] )
{
    if (argc != 2)
    {
        printf("Usage: %s n\n", argv[0]);
        exit(-1);
    }

    int n = atoi(argv[1]);

    #pragma omp parallel if (n > 9) num_threads(4)
    {
        int id = omp_get_thread_num();
        if (id == 0)
        {
            printf("Value of n: %d\n", n);
            printf("Number of threads in parallel region: %d\n", omp_get_num_threads());
        }
    }

    return 0;
}
