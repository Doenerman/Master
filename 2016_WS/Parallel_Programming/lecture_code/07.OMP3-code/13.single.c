#include <stdio.h>
#include <unistd.h>
#include "omp.h"

int main( void )
{
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        #pragma omp single
        {
            printf("[%d] Executed only by any one thread\n", id);
            sleep(3);
        }
        printf("[%d] Executed by all threads\n", id);
    }

    return 0;
}
