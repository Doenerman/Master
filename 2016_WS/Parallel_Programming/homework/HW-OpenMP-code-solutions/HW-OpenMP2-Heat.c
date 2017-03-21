#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define DEBUG 0
#define THRESHOLD (5e-3)

void print_matrix( double *phi, int n )
{
    int i, j;
    for ( i = 0; i < n; i++ )
    {
        printf("[" );
        for ( j = 0; j < n; j++ )
            printf(" %10.6f ", phi[j*n + i] );
        printf("]\n" );
    }
}

void init_phi( double * phi, int n )
{
    int i, j;

    // Interior points initialized to 50 degrees
    for ( i = 1; i < n-1; i++ )
        for ( j = 1; j < n-1; j++ )
            phi[j*n+i] = 50.0;

    // Top, left, and right boundaries fixed at 100 degrees
    for ( i = 0; i < n; i++ )
    {
        phi[    0*n +    i] = 100.0;
        phi[(n-1)*n +    i] = 100.0;
        phi[    i*n +    0] = 100.0;
    }
    // Bottom boundary fixed at 0 degrees
    for ( i = 0; i < n; i++ )
        phi[    i*n +(n-1)] = 0.0;
}

void compute_seq( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
    while( 1 )
    {
        (*niters)++;
#if DEBUG
        printf("Iteration %d\n", niters);
        sleep(1);
#endif
        // Compute next (new) phi from current (old) phi
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                      phi_cur[ j*n+(i-1) ] +
                                      phi_cur[ j*n+(i+1) ] +
                                      phi_cur[ (j+1)*n+i ] ) / 4;
        // If converged, we are done
        conv = 1;
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                    conv = 0;
        if ( conv )
            break;
        // Otherwise, swap pointers and continue
        tmp = phi_cur;
        phi_cur = phi_next;
        phi_next = tmp;
    }

    free( phi_cur );
    free( phi_next );
}

void compute_outer( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
    while( 1 )
    {
        (*niters)++;
#if DEBUG
        printf("Iteration %d\n", niters);
        sleep(1);
#endif
        // Compute next (new) phi from current (old) phi
        #pragma omp parallel for private(i)
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                      phi_cur[ j*n+(i-1) ] +
                                      phi_cur[ j*n+(i+1) ] +
                                      phi_cur[ (j+1)*n+i ] ) / 4;
        // If converged, we are done
        conv = 1;
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                    conv = 0;
        if ( conv )
            break;
        // Otherwise, swap pointers and continue
        tmp = phi_cur;
        phi_cur = phi_next;
        phi_next = tmp;
    }

    free( phi_cur );
    free( phi_next );
}

void compute_inner( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
    while( 1 )
    {
        (*niters)++;
#if DEBUG
        printf("Iteration %d\n", niters);
        sleep(1);
#endif
        // Compute next (new) phi from current (old) phi
        for( j = 1; j < n-1; j++ )
            #pragma omp parallel for
            for( i = 1; i < n-1; i++ )
                phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                      phi_cur[ j*n+(i-1) ] +
                                      phi_cur[ j*n+(i+1) ] +
                                      phi_cur[ (j+1)*n+i ] ) / 4;
        // If converged, we are done
        conv = 1;
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                    conv = 0;
        if ( conv )
            break;
        // Otherwise, swap pointers and continue
        tmp = phi_cur;
        phi_cur = phi_next;
        phi_next = tmp;
    }

    free( phi_cur );
    free( phi_next );
}

void compute_conv( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
    while( 1 )
    {
        (*niters)++;
#if DEBUG
        printf("Iteration %d\n", niters);
        sleep(1);
#endif
        // Compute next (new) phi from current (old) phi
        #pragma omp parallel for private(i)
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                      phi_cur[ j*n+(i-1) ] +
                                      phi_cur[ j*n+(i+1) ] +
                                      phi_cur[ (j+1)*n+i ] ) / 4;
        // If converged, we are done
        conv = 1;
        #pragma omp parallel for private(i) reduction(&&:conv)
        for( j = 1; j < n-1; j++ )
            for( i = 1; i < n-1; i++ )
                if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                    conv = 0;
        if ( conv )
            break;
        // Otherwise, swap pointers and continue
        tmp = phi_cur;
        phi_cur = phi_next;
        phi_next = tmp;
    }

    free( phi_cur );
    free( phi_next );
}

void compute_single_region( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
    while( 1 )
    {
        (*niters)++;
#if DEBUG
        printf("Iteration %d\n", niters);
        sleep(1);
#endif
        conv = 1;
        #pragma omp parallel reduction(&&:conv)
        {
            // Compute next (new) phi from current (old) phi
            #pragma omp for private(i)
            for( j = 1; j < n-1; j++ )
                for( i = 1; i < n-1; i++ )
                    phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                          phi_cur[ j*n+(i-1) ] +
                                          phi_cur[ j*n+(i+1) ] +
                                          phi_cur[ (j+1)*n+i ] ) / 4;
            // If converged, we are done
            #pragma omp for private(i)
            for( j = 1; j < n-1; j++ )
                for( i = 1; i < n-1; i++ )
                    if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                        conv = 0;
        }
        if ( conv )
            break;
        // Otherwise, swap pointers and continue
        tmp = phi_cur;
        phi_cur = phi_next;
        phi_next = tmp;
    }

    free( phi_cur );
    free( phi_next );
}

void compute_while( int n, int *niters )
{
    double *phi_cur, *phi_next, *tmp;
    int conv;
    int i, j;

    phi_cur  = (double *) malloc ( n * n * sizeof(double) );
    phi_next = (double *) malloc ( n * n * sizeof(double) );
    
    init_phi(phi_cur, n);
    init_phi(phi_next, n);

    *niters = 0;
#pragma omp parallel
    while( 1 )
    {
#pragma omp master
        {
            (*niters)++;
#if DEBUG
            printf("Iteration %d\n", niters);
            sleep(1);
#endif
            conv = 1;
        }
        /*#pragma omp parallel reduction(&&:conv)*/
        {
            // Compute next (new) phi from current (old) phi
            #pragma omp for private(i)
            for( j = 1; j < n-1; j++ )
                for( i = 1; i < n-1; i++ )
                    phi_next[ j*n+i ] = ( phi_cur[ (j-1)*n+i ] +
                                          phi_cur[ j*n+(i-1) ] +
                                          phi_cur[ j*n+(i+1) ] +
                                          phi_cur[ (j+1)*n+i ] ) / 4;
            // If converged, we are done
            #pragma omp for private(i) reduction(&&:conv)
            for( j = 1; j < n-1; j++ )
                for( i = 1; i < n-1; i++ )
                    if( fabs( phi_next[ j*n + i ] - phi_cur[ j*n + i ] ) > THRESHOLD )
                        conv = 0;
        }
        if ( conv )
        {
            /*printf("Thread %d exiting the loop\n", omp_get_thread_num());*/
            break;
        }
        // Otherwise, swap pointers and continue
        #pragma omp master
        {
            tmp = phi_cur;
            phi_cur = phi_next;
            phi_next = tmp;
        }
        #pragma omp barrier // CAREFUL!!!
    }

    free( phi_cur );
    free( phi_next );
}

int main( int argc, char *argv[] ) 
{
    int n, niters, nths;
    double t0, t1, tt;
    double seq_t;

    if (argc != 2)
    {
        fprintf( stderr, "Usage: %s <n>\n", argv[0] );
        exit( -1 );
    }

    n = atoi( argv[1] );

    printf("Version             | #iters | #threads | #Time (s) | Speedup \n");
    printf("------------------------------------------------------------- \n");

    t0 = omp_get_wtime();
    compute_seq( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Sequential          | %6d | %8d | %9.2f | %7.2f \n", niters, 1, tt, 1.0); fflush(stdout);
    seq_t = tt;

    nths = atoi( getenv("OMP_NUM_THREADS") );

    t0 = omp_get_wtime();
    compute_outer( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Par. outermost loop | %6d | %8d | %9.2f | %7.2f \n", niters, nths, tt, seq_t/tt); fflush(stdout);

    t0 = omp_get_wtime();
    compute_inner( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Par. innermost loop | %6d | %8d | %9.2f | %7.2f \n", niters, nths, tt, seq_t/tt); fflush(stdout);

    t0 = omp_get_wtime();
    compute_conv( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Par. outer + conv   | %6d | %8d | %9.2f | %7.2f \n", niters, nths, tt, seq_t/tt); fflush(stdout);

    t0 = omp_get_wtime();
    compute_single_region( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Single parallel reg | %6d | %8d | %9.2f | %7.2f \n", niters, nths, tt, seq_t/tt); fflush(stdout);

    t0 = omp_get_wtime();
    compute_while( n, &niters );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Par. while          | %6d | %8d | %9.2f | %7.2f \n", niters, nths, tt, seq_t/tt); fflush(stdout);
    printf("------------------------------------------------------------- \n");

    return 0;
}

