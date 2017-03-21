#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// How to set max priority via library routine
int main( void )
{
    printf("MAX PRIO: %d\n", omp_get_max_task_priority());

    return 0;
}

