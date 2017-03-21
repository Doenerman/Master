#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct {
    int x;
    int y;
} tuple;

int main( void )
{
    tuple t;

    t.x = 0;
    t.y = 0;

    // Structure is shared among threads
    //
    printf("Struct is shared\n");
    printf("\tBefore parallel region: (%d,%d)\n", t.x, t.y);
    #pragma omp parallel num_threads(2) shared(t)
    {
        int id = omp_get_thread_num();
        t.x = t.y = id+1;

        printf("\t(%d) In parallel region: (%d,%d)\n", id, t.x, t.y);
    }
    printf("\tAfter parallel region:  (%d,%d)\n", t.x, t.y);

    // Structure is private to each thread
    //
    t.x = t.y = 0;
    printf("Struct is private\n");
    printf("\tBefore parallel region: (%d,%d)\n", t.x, t.y);
    #pragma omp parallel num_threads(2) private(t)
    {
        int id = omp_get_thread_num();
        t.x = t.y = id+1;

        printf("\t(%d) In parallel region: (%d,%d)\n", id, t.x, t.y);
    }
    printf("\tAfter parallel region:  (%d,%d)\n", t.x, t.y);

    // t.x is private
    // This code raises a compilation error
    /*
    t.x = t.y = 0;
    printf("t.x is private\n");
    printf("\tBefore parallel region: (%d,%d)\n", t.x, t.y);
    #pragma omp parallel num_threads(2) private(t.x)
    {
        int id = omp_get_thread_num();
        t.x = t.y = id+1;

        printf("\t(%d) In parallel region: (%d,%d)\n", id, t.x, t.y);
    }
    printf("\tAfter parallel region:  (%d,%d)\n", t.x, t.y);
    */

    return 0;
}
