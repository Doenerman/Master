// Dot product - reduction
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 6
#define NUMBER_OF_THREADS 2

int main(int argc, char *argv[])
{
    // Computes alpha = alpha + x' * y  -->   alpha = alpha + \Sum_i (x[i] * y[i])
    double x[N], y[N], alpha;
    int i;

    alpha = 2.0;
    for( i = 0; i < N; i++ )
    {
        x[i] = i;
        y[i] = i;
    }

    #pragma omp parallel reduction(+:alpha) private(i)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();
        for ( i = id; i < N; i += nths )
            alpha = alpha + x[i] * y[i];
    }

    printf("Alpha is: %.2f\n", alpha);

    return 0;
}

