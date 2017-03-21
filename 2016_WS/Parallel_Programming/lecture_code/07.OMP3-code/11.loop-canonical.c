#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 10
#define NUMBER_OF_THREADS 2

struct list {
    int elem;
    struct list *next;
};

void print_array( double *array, int size )
{
    int i;
    printf("[ ");
    for( i = 0; i < size; i++ )
        printf("%.1f ", array[i] );
    printf("]\n");
}

int main(int argc, char *argv[])
{
    // Computes z = alpha * x + y
    double x[N], y[N], z[N], alpha;
    int i;

    alpha = 5.0;
    for( i = 0; i < N; i++ )
    {
        x[i] = i;
        y[i] = 2.0*i;
    }

    // Axpy, increasing index
    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        #pragma omp for
        for ( i = 0; i < N; i++ )
            z[i] = alpha * x[i] + y[i];
    }
    print_array( z, N );

    // Axpy, decreasing index
    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        #pragma omp for
        for ( i = N-1; i >= 0; i-- )
            z[i] = alpha * x[i] + y[i];
    }
    print_array( z, N );

    // Scales z with alpha
    double *p_z = z;
    double *iter;
    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        #pragma omp for
        for ( iter = p_z; iter < p_z+N; iter++ )
            *iter = alpha * *iter;
    }
    print_array( z, N );

    // Scales z  = alpha * x (wrong loop form)
/*  double *p_x = x;
    double *iter_x,
           *iter_z;
    #pragma omp parallel num_threads(NUMBER_OF_THREADS) // private(?)
    {
        #pragma omp for
        for ( iter_z = p_z, iter_x = p_x; iter_z < p_z+N; iter_z++, iter_x++ )
            *iter_z = alpha * *iter_x;
    }
    print_array( z, N );
*/

    // Traverses and "processes" a linked list (wrong loop form as well)

    struct list start, end, *list_iter;
    start.elem = 0;
    start.next = &end;
    end.elem = 1;
    end.next = NULL;
    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        #pragma omp for
        for ( list_iter = &start; list_iter != NULL; list_iter = list_iter->next )
        {
            // process( iter );
        }
    }


    return 0;
}

