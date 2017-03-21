#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 10

int main(int argc, char *argv[])
{
    int i;
    int sum;

    sum = 0;
    #pragma omp parallel
    {
        #pragma omp for reduction(+:sum)
        for ( i = 0; i < N; i++ ) {
            sum += i;
        }
    }

    printf("Sum:   %d (45?)\n", sum);

    return 0;
}

