#include <stdio.h>
#include "omp.h"

int main( void )
{
    #pragma omp parallel num_threads(3)
    {
        int id = omp_get_thread_num();
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Section 1 executed by thread %d\n", id);
            }
            #pragma omp section
            {
                printf("Section 2 executed by thread %d\n", id);
            }
            #pragma omp section
            {
                printf("Section 3 executed by thread %d\n", id);
            }
            #pragma omp section
            {
                printf("Section 4 executed by thread %d\n", id);
            }
            #pragma omp section
            {
                printf("Section 5 executed by thread %d\n", id);
            }
            #pragma omp section
            {
                printf("Section 6 executed by thread %d\n", id);
            }
        }
    }

    return 0;
}
