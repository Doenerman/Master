#include <stdio.h>

int main( void )
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int i;

    for (i = 1; i < 10; i++)
        a[i] = a[i] + a[i-1];

    // 0  1  3  6  10  15  21  28  36  45 
    for (i = 0; i < 10; i++)
        printf(" %d ", a[i]);
    printf("\n");

    return 0;
}
