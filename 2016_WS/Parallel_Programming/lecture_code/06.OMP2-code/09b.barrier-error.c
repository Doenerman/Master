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
            printf("Thread %d reaching the first barrier\n", id);
            #pragma omp barrier
        }
        else // Threads 2 and 3
        {
            // do some work
            printf("Thread %d reaching the second barrier\n", id);
            #pragma omp barrier
        }

        // The code above does not comply with OpenMP standard.
        // Thus the behavior is unspecified. The fact that the
        // line below is printed is just pure chance (in other
        // words, implementation dependent and not portable).

        printf("[%d] This should not get printed\n", id);
    }

    return 0;
}
