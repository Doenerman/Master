#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 4
#define NUMBER_OF_THREADS 2

int main(int argc, char *argv[])
{
    #pragma omp parallel num_threads(2)
    {
        int i;
        int id = omp_get_thread_num();

        printf("Thread %d reporting for duty\n", id);

        #pragma omp barrier

#pragma omp sections
        {
#pragma omp section  // Thread 0
            {
                #pragma omp parallel for // Threads 0 - 2 3 4
                for (i = 0; i < 4; i++)
                    printf("Thread %d executes first loop - iteration %d\n", id, i);
                // Wait 0 2 3 4
            } 
#pragma omp section // Thread 1
            {
                #pragma omp parallel for
                for (i = 0; i < 4; i++)
                    printf("Thread %d executes second loop - iteration %d\n", id, i);
            }
        }
    }

    return 0;
}

