#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 10
#define NUMBER_OF_THREADS 2

int main(int argc, char *argv[])
{
    // Computes z = alpha * x + y
    double x[N], y[N], z[N], alpha;
    int i;

    alpha = 5.0;
    for( i = 0; i < N; i++ )
    {
        x[i] = i;
        y[i] = 2.0*i;
    }

    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();
        printf("Thread %d of %d ready!\n", id, nths);

        // Distribute iterations in chunks of N/nths
        int chunk = N/nths;
        int start = id * chunk;
        int end = (id+1) * chunk; 
        if ( id == nths-1 ) // In case N is not perfectly divisible by nths
            end = N;

        int j;
        // Thread 0 computes iterations [0 to 4]
        // Thread 1 computes iterations [5 to 9]
        for ( j = start; j < end; j++ ) {
            z[j] = alpha * x[j] + y[j];
        }
    }

    // Print results. Should output [0, 7, 14, 21, ...]
    printf("[ ");
    for( i = 0; i < N; i++ )
        printf("%.1f ", z[i] );
    printf("]\n");

    return 0;
}

