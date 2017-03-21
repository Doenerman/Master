#include <stdio.h>

int main( void )
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int b[10] = {9,8,7,6,5,4,3,2,1,0};
    int i, tmp;

    for (i = 0; i < 10; i++) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }

    // A:  9  8  7  6  5  4  3  2  1  0 
    // B:  0  1  2  3  4  5  6  7  8  9 
    printf("A: ");
    for (i = 0; i < 10; i++)
        printf(" %d ", a[i]);
    printf("\n");

    printf("B: ");
    for (i = 0; i < 10; i++)
        printf(" %d ", b[i]);
    printf("\n");

    return 0;
}
