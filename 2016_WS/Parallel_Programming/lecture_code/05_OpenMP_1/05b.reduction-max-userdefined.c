#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define N 10

int my_max_function( int omp_out, int omp_in )
{
   if ( omp_out > omp_in )
      return omp_out;
   else
      return omp_in;
}

//#pragma omp declare reduction( mymax : int : omp_out = omp_in > omp_out ? omp_in : omp_out ) \
                                             initializer( omp_priv = MIN_INT )
#pragma omp declare reduction( mymax : int : omp_out = my_max_function( omp_out, omp_in ) ) \
                                             initializer( omp_priv = INT_MIN )

int main( void )
{
    int i, data[N];
    int max = INT_MIN; // Initialize to the minimum possible integer

    for (i = 0; i < N; i++)
        data[i] = rand() % 100;

    // Checking
    printf("[%d ", data[0]);
    for (i = 1; i < N; i++)
        printf(", %d", data[i]);
    printf("]\n");

    #pragma omp parallel reduction(mymax:max) private(i)
    {
        int id = omp_get_thread_num();
        int nths = omp_get_num_threads();
        for (i = id; i < N; i += nths)
        {
            if (data[i] > max)
                max = data[i];
        }
    }

    // Checking
    printf("Max: %d\n", max);

    return 0;
}
