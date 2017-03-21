#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define DEBUG 0

int main( int argc, char *argv[] )
{
    int i, nsamples, nbuckets;
    int *hist, *data;

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

    // Fill in the histogram
    for ( i = 0; i < nsamples; i++ )
        hist[ data[i] ] += 1;

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
