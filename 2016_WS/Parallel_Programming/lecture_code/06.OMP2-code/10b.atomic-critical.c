#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

int main( void )
{
    int ctr = 0;

    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();

        int i;
        for( i = id; i < N; i += nths ) {
            if ( id == 0 ) {
                #pragma omp critical
                ctr = ctr + 1;
            } else {
                #pragma omp atomic
                ctr = ctr + 1;
            }
        }
    }

    printf("Ctr: %d (%d)\n", ctr, N);

    return 0;
}
