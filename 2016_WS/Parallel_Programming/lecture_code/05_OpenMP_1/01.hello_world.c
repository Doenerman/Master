// Sequential code
// gcc 01a.hello_world.c -o 01a.hello_world.x
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main( void )
{
    #pragma omp parallel num_threads(4)
    {
    	printf("Hello world!\n");
    }
    return 0;
}
