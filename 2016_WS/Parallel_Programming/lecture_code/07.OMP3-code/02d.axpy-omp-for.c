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
        #pragma omp for
        for ( i = 0; i < N; i++ )
            z[i] = alpha * x[i] + y[i];
    }

    // Print results. Should output [0, 7, 14, 21, ...]
    printf("[ ");
    for( i = 0; i < N; i++ )
        printf("%.1f ", z[i] );
    printf("]\n");

    return 0;
}

