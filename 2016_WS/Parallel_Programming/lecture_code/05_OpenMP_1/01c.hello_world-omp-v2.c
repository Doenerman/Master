// Setting the number of threads (6 in the examples)
// gcc -fopenmp 01c.hello_world-omp-v2.c -o 01c.hello_world-omp-v2.x
//
// export OMP_NUM_THREADS=6; ./01c.hello_world-omp-v2.x
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main( void )
{
    // omp_set_num_threads( 6 );
    #pragma omp parallel // num_threads(6)
    {
        printf("Hello world!\n");
    }

    return 0;
}
