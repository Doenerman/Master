#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char *argv[])
{
    int i, n, nths;

    if (argc != 3)
    {
        printf("Usage: %s n nths\n", argv[0]);
        exit(-1);
    }

    n = atoi(argv[1]);
    nths = atoi(argv[2]);
    #pragma omp parallel num_threads( nths )
    {
        #pragma omp for
        for ( i = 0; i < n; i++ )
        {
            printf("Thread %d executes iteration %d\n",
                    omp_get_thread_num(), i);
        }
    }

    return 0;
}

