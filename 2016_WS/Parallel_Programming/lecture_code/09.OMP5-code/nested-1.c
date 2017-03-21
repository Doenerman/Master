#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( void )
{
    int i, j, n = 5;

    // Try also uncommenting the line below
    // omp_set_nested(1);
    printf("Nested? %s\n", omp_get_nested() ? "TRUE" : "FALSE" );
    #pragma omp parallel for num_threads(4)
    for ( i = 0; i < n; i++ ) {
        printf( "Num threads: %d\n", omp_get_num_threads());
        #pragma omp parallel for num_threads(4)
        for ( j = 0; j < n; j++ ) {
            printf( "\tNum threads: %d\n", omp_get_num_threads());
        }
    }
}
