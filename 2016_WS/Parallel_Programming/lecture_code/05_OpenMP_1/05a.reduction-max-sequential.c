#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define N 10

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

    for (i = 0; i < N; i++ )
    {
        if (data[i] > max)
            max = data[i];
    }

    // Checking
    printf("Max: %d\n", max);

    return 0;
}
