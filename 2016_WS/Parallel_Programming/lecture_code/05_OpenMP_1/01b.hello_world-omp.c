// Parallel version 1
// gcc -fopenmp 01b.hello_world-omp.c -o 01b.hello_world-omp.x
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main( void )
{
    #pragma omp parallel num_threads(4)
    {
	int id = omp_get_thread_num();
        printf("Hello world! I am thread %d \n",id);
    }

    return 0;
}
