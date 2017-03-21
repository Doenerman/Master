#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( void )
{
    int A, B, C;

    A = 1;
    B = 1;
    C = 1;
    #pragma omp parallel num_threads(2) \
        default(none) shared(A) private(B) firstprivate(C)
    {
        int id = omp_get_thread_num();
        printf("Thread %d - Value of A in parallel region: %d\n", id, A);
        printf("Thread %d - Value of B in parallel region: %d\n", id, B);
        printf("Thread %d - Value of C in parallel region: %d\n", id, C);

       /* A = 2;
        B = 2;
        C = 2;
        printf("Thread %d - New value of A in parallel region: %d\n", id, A);
        printf("Thread %d - New value of B in parallel region: %d\n", id, B);
        printf("Thread %d - New value of C in parallel region: %d\n", id, C); */
    }
    printf("Value of A after parallel region: %d\n", A);
    printf("Value of B after parallel region: %d\n", B);
    printf("Value of C after parallel region: %d\n", C);

    return 0;
}
