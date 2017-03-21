// Sequential version
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 10

int main(int argc, char *argv[])
{
    // Computes z = alpha * x + y
    double x[N], y[N], z[N], alpha;

    alpha = 5.0;
    #pragma omp parallel num_threads(4)
    {
	int id = omp_get_thread_num();
	int numThreads = omp_get_num_threads();
	int i;
        for( i = id; i < ((id + 1) *N/numThreads); i++ )
        {
            x[i] = i;
            y[i] = 2.0*i;
        }
    }
    #pragma omp parallel num_threads(4)
    {
	int i;
        for(i = omp_get_thread_num(); i < (4*N/omp_get_num_threads()); i++) 
            z[i] = alpha * x[i] + y[i];
    }

    // Print results. Should output [0, 7, 14, 21, ...]
    printf("[ ");
	int i;
    for( i = 0; i < N; i++ )
        printf("%.1f ", z[i] );
    printf("]\n");

    return 0;
}

