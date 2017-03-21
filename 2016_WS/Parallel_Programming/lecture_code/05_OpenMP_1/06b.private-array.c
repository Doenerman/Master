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
    int a[N];

    printf("Before parallel region: "); print_array( a, N );
    #pragma omp parallel num_threads(2) private(a)
    {
        int id = omp_get_thread_num();
        a[id] = id+1;
        printf("Thread %d: ", id); print_array( a, N );
    }
    printf("After parallel region: "); print_array( a, N );

    return 0;
}
