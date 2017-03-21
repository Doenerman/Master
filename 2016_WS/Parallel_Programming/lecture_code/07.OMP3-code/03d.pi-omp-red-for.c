#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define NUM_STEPS 1000000
#define NUM_THREADS 4

int main( void )
{
    double sum = 0.0, pi;
    double step = 1.0/NUM_STEPS;

    #pragma omp parallel reduction(+:sum)
    {
        int i;
        double x_i;

        #pragma omp for
        for ( i = 0; i < NUM_STEPS; i++ )
        {
            x_i = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x_i * x_i);
        }
    }
    pi = sum * step;

    printf("Pi: %.15e\n", pi);

    return 0;
}
