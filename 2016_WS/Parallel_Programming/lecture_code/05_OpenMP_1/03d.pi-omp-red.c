#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define NUM_STEPS 1000000
#define NUM_THREADS 4

int main( void )
{
    int i;
    double sum = 0.0, pi, x_i;
    double step = 1.0/NUM_STEPS;

    #pragma omp parallel num_threads(NUM_THREADS) private(i, x_i) reduction(+:sum)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();

        for ( i = id; i < NUM_STEPS; i += nths )
        {
            x_i = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x_i * x_i);
        }
    }
    pi = sum * step;

    printf("Pi: %.15e\n", pi);

    return 0;
}
