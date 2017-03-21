#include <stdio.h>
#include <stdlib.h>

#define NUM_STEPS 10000

int main( void )
{
    int i;
    double sum = 0.0, pi, x_i;
    double step = 1.0/NUM_STEPS;

    for ( i = 0; i < NUM_STEPS; i++ )
    {
        x_i = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x_i * x_i);
    }
    pi = sum * step;

    printf("Pi: %.15e\n", pi);

    return 0;
}
