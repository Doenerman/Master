#include <stdio.h>

int main( void )
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int i;

    for (i = 0; i < 9; i++)
        a[i] = a[i+1] + i; // f(i) -> i

    //  1  3  5  7  9  11  13  15  17  9 
    for (i = 0; i < 10; i++)
        printf(" %d ", a[i]);
    printf("\n");

    return 0;
}
