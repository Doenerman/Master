#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 4
#define NUMBER_OF_THREADS 2

int main(int argc, char *argv[])
{
    int i, j;
    #pragma omp parallel num_threads( NUMBER_OF_THREADS )
    {
        int id = omp_get_thread_num();
        #pragma omp for private(i,j) ordered schedule(static,2) collapse(2)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                #pragma omp ordered
                printf("Thread %d executes iteration (%d,%d)\n", id, i, j);
    }

    return 0;
}

