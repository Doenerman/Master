#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( void )
{
    int i, j, k, n = 5;

    omp_set_nested(1);

    printf("Max active levels: %d\n", omp_get_max_active_levels());
    // Try also uncommenting the line below
    // omp_set_max_active_levels(2);

    #pragma omp parallel for num_threads(4)
    for ( i = 0; i < n; i++ ) {
        printf( "Num threads: %d\n", omp_get_num_threads());
        #pragma omp parallel for num_threads(4)
        for ( j = 0; j < n; j++ ) {
            printf( "\tNum threads: %d\n", omp_get_num_threads());
            #pragma omp parallel for num_threads(4)
            for ( k = 0; k < n; k++ ) {
                printf( "\t\tNum threads: %d\n", omp_get_num_threads());
            }
        }
    }
}
