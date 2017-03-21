#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

#define NUM_POINTS 4000000
#define RADIUS 1.0

int main( void )
{
    long int i, count;
    double x, y;
    double pi;

    // initialize the seed here!!!
    count = 0;
    #pragma omp parallel reduction(+:count)
    {
        #pragma omp for
        for ( i = 0; i < NUM_POINTS; i++ )
        {
            x = drand48();
            y = drand48();

            if ( sqrt(x*x+y*y) <= RADIUS )
                count += 1;
        }
    }

    pi = 4 * (double)count/NUM_POINTS;

    printf("Pi: %.15e\n", pi);

    return 0;
}
