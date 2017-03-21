// Try different options:
//   - no names in the critical directives
//   - same name in the critical directives
//   - different names in the critical directives
#include <stdio.h>
#include <unistd.h>
#include <omp.h>

#include "timing.h"

#define N 6

int main( void )
{
    unsigned long ticksB4, ticksAFT, ticks;
    double freq = 2.0e9;  

    get_ticks(ticksB4);

    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();

        int i;
        for( i = id; i < N; i += nths ) {
            if ( id == 0 ) {
                #pragma omp critical (th0)
                sleep(1);
            } else {
                #pragma omp critical (th0)
                sleep(1);
            }
        }
    }

    get_ticks(ticksAFT);
    ticks = ticksAFT - ticksB4;
    printf(" Time: %.3g\n", (double) ticks/freq );

    return 0;
}
