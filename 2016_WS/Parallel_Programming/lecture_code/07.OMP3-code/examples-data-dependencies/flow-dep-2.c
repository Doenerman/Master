#include <stdio.h>

int main( void )
{
    int a[10];
    int i, j;

    j = 5;
    for (i = 0; i < 10; i++) {
        j += 2;
        a[i] = j; // f(j) -> j
    }

    //  7  9  11  13  15  17  19  21  23  25 
    for (i = 0; i < 10; i++)
        printf(" %d ", a[i]);
    printf("\n");

    return 0;
}
