#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// assumes size >= 1
void print_array( int *array, int size )
{
    int i;
    printf("[%d", array[0]);
    for (i = 1; i < size; i++)
        printf(", %d", array[i]);
    printf("]\n");
}

int main( void )
{
    int N = 5;
    int *a = malloc( N * sizeof(int) );

    int i;
    for (i = 0; i < N; i++)
        a[i] = 0;

    printf("Before parallel region: (%p) ", a); print_array( a, N );
    #pragma omp parallel num_threads(2) firstprivate(a) // Try also private(a) instead
    {
        int id = omp_get_thread_num();
        a[id] = id+1;
        printf("Thread %d (%p): ", id, a); print_array( a, N );
    }
    printf("After parallel region: (%p)", a); print_array( a, N );

    free(a);

    return 0;
}
