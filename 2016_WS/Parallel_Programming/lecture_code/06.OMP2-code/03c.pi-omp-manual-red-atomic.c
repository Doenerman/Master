#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_STEPS 10000
#define NUM_THREADS 4

int main( void )
{
    int i;
    double sum = 0.0, pi, x_i;
    double step = 1.0/NUM_STEPS;

    #pragma omp parallel num_threads(NUM_THREADS) private(i, x_i)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();
        double local_sum = 0.0; // Initialize local partial sum

        for ( i = id; i < NUM_STEPS; i += nths )
        {
            x_i = (i + 0.5) * step;
            local_sum = local_sum + 4.0 / (1.0 + x_i * x_i); // accumulate to local sum
        }
        #pragma omp atomic
        sum = sum + local_sum; // add partial local sum to global sum in mutual exclusion
    }

    pi = sum * step;

    printf("Pi: %.15e\n", pi);

    return 0;
}
