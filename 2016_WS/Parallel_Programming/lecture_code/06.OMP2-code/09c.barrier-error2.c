#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

int main( void )
{
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        if ( id < 2 ) // Threads 0 and 1
        {
            // do some work
            printf("Thread %d reaching the barrier\n", id);
            #pragma omp barrier
        }

        // If the team consists of more than 2 threads,
        // threads 0 and 1 should never reach the point below.

        printf("Thread %d ready to exit the parallel region\n", id);
    }

    return 0;
}
