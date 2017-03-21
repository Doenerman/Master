// Sequential
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define NUM_STEPS 10000
#define THREAD_NUMS 4

int main( void )
{
    double sum = 0.0, pi, x_i;
    double step = 1.0/NUM_STEPS;
	
    #pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		int maxID = omp_get_num_threads();
		int i;
    	for ( i = id; i < ((id + 1)/maxID)*NUM_STEPS; i++ )
    	{
        	x_i = (i + 0.5) * step;
			#pragma omp atomic
        	sum = sum + 4.0 / (1.0 + x_i * x_i);
    	}
	}
    pi = sum * step;

    printf("Pi: %.15e\n", pi);

    return 0;
}
