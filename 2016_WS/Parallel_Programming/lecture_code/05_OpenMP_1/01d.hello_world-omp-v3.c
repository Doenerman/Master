// This code contains a data race condition
//  id is a shared variable and all threads write to it
//  the call to function sleep is introduced to expose the problem
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "omp.h"

int main( void )
{
    int id, nths;
    #pragma omp parallel
    {
        // declare id and nths here to avoid the race condition
        // int id, nths; // now they're private to each thread
        id = omp_get_thread_num();
        nths = omp_get_num_threads();
        sleep(1);
        printf("Hello world! I'm thread %d of %d\n", id, nths);
    }

    return 0;
}
