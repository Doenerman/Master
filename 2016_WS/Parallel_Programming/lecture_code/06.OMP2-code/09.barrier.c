#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( void )
{
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        printf("[Thread %d] Before barrier\n", id);

        // No one goes beyond this barrier before 
        // every thread checks in
        #pragma omp barrier

        printf("[Thread %d] After barrier\n", id);
    }

    return 0;
}
