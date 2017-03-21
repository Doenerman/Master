#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <omp.h>

#include "timing.h"

#define DEBUG 0

int main( int argc, char *argv[] )
{
    int i, nsamples, nbuckets;
    int *hist, *data;

    unsigned long ticksB4, ticksAFT, ticks;
    double freq = 2.0e9;  

    if ( argc != 3 )
    {
        fprintf( stderr, "Usage: %s nsamples nbuckets\n", argv[0] );
        exit( -1 );
    }

    nsamples = atoi( argv[1] );
    nbuckets = atoi( argv[2] );

    hist = (int *) malloc (nbuckets * sizeof(int));
    data = (int *) malloc (nsamples * sizeof(int));

    // Initialize the histogram and the dataset
    for ( i = 0; i < nbuckets; i++ )
        hist[i] = 0;
    for ( i = 0; i < nsamples; i++ )
        data[i] = rand() % nbuckets;

#if DEBUG
    printf("[");
    // Print out data for debugging purposes
    for ( i = 0; i < nsamples; i++ )
        printf(" %d ", data[i]);
    printf("]\n");
#endif

    get_ticks(ticksB4);
    
    // Fill in the histogram
    #pragma omp parallel private(i)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();

        for( i = id; i < nsamples; i += nths )
            #pragma omp atomic
            hist[ data[i] ] += 1;
    }

    get_ticks(ticksAFT);
    ticks = ticksAFT - ticksB4;
    printf(" Atomic: %.3g\n", (double) ticks/freq );

#if DEBUG
    printf("[");
    // Print out data for debugging purposes
    for ( i = 0; i < nbuckets; i++ )
        printf(" %d ", hist[i]);
    printf("]\n");
#endif
    int sum = 0;
    for ( i = 0; i < nbuckets; i++ )
        sum += hist[i];
    assert( sum == nsamples );

    free(hist);
    free(data);

    return 0;
}
