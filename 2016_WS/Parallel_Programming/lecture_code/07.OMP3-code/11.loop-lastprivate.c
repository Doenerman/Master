#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 5
#define NUMBER_OF_THREADS 3

int main(int argc, char *argv[])
{
    int a;
    int i;

    #pragma omp parallel num_threads( NUMBER_OF_THREADS )
    {
        #pragma omp for lastprivate(a)
        for ( i = 0; i < N; i++ )
        {
            a = i+1;
            printf("Thread %d has a value of a = %d for i = %d\n",
                    omp_get_thread_num(), a, i);
        }
    }
    printf("Value of a after parallel for: a = %d\n", a);

    return 0;
}

