#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <omp.h>

double constant( int iter, int n );
double small_fluctuation( int iter, int n );
double increasing( int iter, int n );
double big_fluctuation( int iter, int n );

int main( void )
{
    int i, n = 100000;
    double t0, t1;

    t0 = omp_get_wtime();
    #pragma omp parallel for schedule(runtime)
    for ( i = 0; i < n; i++ )
        constant(i, n);
    t1 = omp_get_wtime();
    printf("Constant work:      %f\n", t1 - t0);

    t0 = omp_get_wtime();
    #pragma omp parallel for schedule(runtime)
    for ( i = 0; i < n; i++ )
        small_fluctuation(i, n);
    t1 = omp_get_wtime();
    printf("Small fluctuations: %f\n", t1 - t0);

    t0 = omp_get_wtime();
    #pragma omp parallel for schedule(runtime)
    for ( i = 0; i < n; i++ )
        increasing(i, n);
    t1 = omp_get_wtime();
    printf("Increasing:         %f\n", t1 - t0);

    t0 = omp_get_wtime();
    #pragma omp parallel for schedule(runtime)
    for ( i = 0; i < n; i++ )
        big_fluctuation(i, n);
    t1 = omp_get_wtime();
    printf("Big fluctuations:   %f\n", t1 - t0);

    return 0;
}

double constant( int iter, int n )
{
    int i;
    double x = 0.0;
    for ( i = 0; i < n; i++ )
        x += sin(i);
    return x;
}

double small_fluctuation( int iter, int n )
{
    int fluc = rand() % 11;
    int niters = (int)(n*(1+fluc/100.));
    int i;
    double x = 0.0;
    for ( i = 0; i < niters; i++ )
        x += sin(i);
    return x;
}

double increasing( int iter, int n )
{
    int i;
    double x = 0.0;
    for ( i = 0; i < iter; i++ )
        x += sin(i);
    return x;
}

double big_fluctuation( int iter, int n )
{
    int prob = rand() % 100;
    int niters;
    if ( iter < 50 )
    {
        if ( prob < 5 )
            niters = 10000000;
        else
            niters = 10;
    }
    else
        niters = 100;

    int i;
    double x = 0.0;
    for ( i = 0; i < niters; i++ )
        x += sin(i);
    return x;
}

