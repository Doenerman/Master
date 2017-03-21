// Now id and nths are private. The data race
// condition is not present anymore
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "omp.h"

int main( void )
{
    #pragma omp parallel
    {
        int id, nths;
        id = omp_get_thread_num();
        nths = omp_get_num_threads();
        sleep(1);
        printf("Hello world! I'm thread %d of %d\n", id, nths);
    }

    return 0;
}
