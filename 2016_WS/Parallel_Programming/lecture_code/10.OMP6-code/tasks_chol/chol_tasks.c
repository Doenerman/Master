#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "timing.h"
#include "mkl_service.h"

#include "include/blas.h"
#include "include/lapack.h"

#include "omp.h"

#define NBLOCKS 24
#define BSIZE 128

/*
 * Utils
 */
void init_spd( double *A, int n )
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i*n+j] = (double)rand() / RAND_MAX;
    for (i = 0; i < n; i++)
        A[i*n+i] += n;
}

void copy_flat_to_hier( double *A_flat, double *A_hier[NBLOCKS][NBLOCKS], int n )
{
    int i, j, jj;
    // For each block
    for (i = 0; i < NBLOCKS; i++) {
        for (j = 0; j < NBLOCKS; j++) {
            // For each column, copy the entire column
            for (jj = 0; jj < BSIZE; jj++) {
                memcpy( &A_hier[i][j][jj*BSIZE], &A_flat[(j*BSIZE+jj)*n + i*BSIZE], BSIZE*sizeof(double) );
            }
        }
    }
}

void check_diff( double *A_flat, double *A_hier[NBLOCKS][NBLOCKS], int n, double threshold )
{
    int i, j, ii, jj;
    double diff;

    for (i = 0; i < NBLOCKS; i++) {
        for (j = 0; j < NBLOCKS; j++) {
            for (jj = 0; jj < BSIZE; jj++) {
                for (ii = 0; ii < BSIZE; ii++) {
                    diff = fabs(A_flat[(j*BSIZE+jj)*n+(i*BSIZE+ii)] - A_hier[i][j][jj*BSIZE+ii]);
                    if ( diff > threshold ) {
                        fprintf(stderr, "[ERROR] Difference: %.15e (%d, %d, %d, %d)\n", diff, i, j, ii, jj);
                        exit(-1);
                    }
                }
            }
        }
    }
}

/*
 * Task-based Cholesky factorization
 */
void chol_hier( double *A[NBLOCKS][NBLOCKS] )
{
    int i, j, k;
    int bs = BSIZE;
    double dONE = 1.0, dMINUS_ONE = -1.0;
    int info;

    #pragma omp parallel private(i, j, k)
    #pragma omp single
    {
        for (k = 0; k < NBLOCKS; k++) {
            #pragma omp task depend(inout:A[k][k])
            dpotrf_("L", &bs, A[k][k], &bs, &info);
            for (i = k+1; i < NBLOCKS; i++ )
                #pragma omp task depend(in:A[k][k]) depend(inout:A[i][k])
                dtrsm_("R", "L", "T", "N", &bs, &bs, &dONE, A[k][k], &bs, A[i][k], &bs);
            for (i = k+1; i < NBLOCKS; i++ ) {
                for (j = k+1; j < i; j++)
                    #pragma omp task depend(in:A[i][k],A[j][k]) depend(inout:A[i][j])
                    dgemm_("N", "T", &bs, &bs, &bs, &dMINUS_ONE, A[i][k], &bs, A[j][k], &bs, &dONE, A[i][j], &bs);
                #pragma omp task depend(in:A[i][k]) depend(inout:A[i][i])
                dsyrk_("L", "N", &bs, &bs, &dMINUS_ONE, A[i][k], &bs, &dONE, A[i][i], &bs);
            }
        }
    }
}

void chol_hier_prio( double *A[NBLOCKS][NBLOCKS] )
{
    int i, j, k;
    int bs = BSIZE;
    double dONE = 1.0, dMINUS_ONE = -1.0;
    int info;

    #pragma omp parallel private(i, j, k)
    #pragma omp single
    {
        for (k = 0; k < NBLOCKS; k++) {
            #pragma omp task depend(inout:A[k][k]) priority(1)
            dpotrf_("L", &bs, A[k][k], &bs, &info);
            for (i = k+1; i < NBLOCKS; i++ )
                #pragma omp task depend(in:A[k][k]) depend(out:A[i][k])
                dtrsm_("R", "L", "T", "N", &bs, &bs, &dONE, A[k][k], &bs, A[i][k], &bs);
            for (i = k+1; i < NBLOCKS; i++ ) {
                for (j = k+1; j < i; j++)
                    #pragma omp task depend(in:A[i][k],A[j][k]) depend(out:A[i][j])
                    dgemm_("N", "T", &bs, &bs, &bs, &dMINUS_ONE, A[i][k], &bs, A[j][k], &bs, &dONE, A[i][j], &bs);
                #pragma omp task depend(in:A[i][k]) depend(out:A[i][i])
                dsyrk_("L", "N", &bs, &bs, &dMINUS_ONE, A[i][k], &bs, &dONE, A[i][i], &bs);
            }
        }
    }
}

int main( void )
{
    int n = NBLOCKS * BSIZE;
    double *A_flat; //[n*n]; // Flat to compare with mkl
    double *A[NBLOCKS][NBLOCKS]; // Hierarchical for example purposes

    int i, j;
    int nths;
    int info;
    int rep, nreps = 10; 
    double t0, t1, tt;
    
    unsigned long ticksB4, ticksAFT, ticks;
    double freq = 2.0e9;  

    int debug = 0; // Test correctness (1) or run performance experiment (0)


    // Allocate flat and initialize symmetric positive definite matrix
    A_flat = (double *) malloc (n*n*sizeof(double));
    init_spd( A_flat, n );

    // Allocate hierarchical and copy
    for (i = 0; i < NBLOCKS; i++)
        for (j = 0; j < NBLOCKS; j++)
            A[i][j] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
    copy_flat_to_hier( A_flat, A, n );

    // Make sure the copy is ok
    check_diff( A_flat, A, n, 1e-15 );
    printf("Setup ok\n");

    if ( debug )
    {
        // Run well-tested library
        dpotrf_("L", &n, A_flat, &n, &info);
        // Run my code
        chol_hier( A );
        // Check results
        check_diff( A_flat, A, n, 1e-10 );
        // If wrong, function check_diff would force the program to abort
        printf("Results OK\n");
    }
    else
    {
        printf("Version             | #threads | #Time (s) | Speedup \n"); // Speedup wrt the base case
        printf("---------------------------------------------------- \n");

        // TIC
        get_ticks(ticksB4);
        // Compute
        for (rep = 0; rep < nreps; rep++)
            dpotrf_("L", &n, A_flat, &n, &info);
        // TOC
        get_ticks(ticksAFT);
        ticks = ticksAFT - ticksB4;
        double tt_seq = (double) ticks/freq;
        printf("Sequential          | %8d | %9.2f | %7.2f \n", 1, tt_seq, 1.0);
        printf("---------------------------------------------------- \n");

        for (nths = 2; nths <= 8; nths *= 2)
        {
            omp_set_num_threads( nths );
            // TIC
            get_ticks(ticksB4);
            // Compute
            for (rep = 0; rep < nreps; rep++)
                chol_hier( A );
            // TOC
            get_ticks(ticksAFT);
            ticks = ticksAFT - ticksB4;
            tt = (double) ticks/freq;
            printf("Task based          | %8d | %9.2f | %7.2f \n", nths, tt, tt_seq / tt);
        }
        printf("---------------------------------------------------- \n");

        for (nths = 2; nths <= 8; nths *= 2)
        {
            omp_set_num_threads( nths );
            // TIC
            get_ticks(ticksB4);
            // Compute
            for (rep = 0; rep < nreps; rep++)
                chol_hier_prio( A );
            // TOC
            get_ticks(ticksAFT);
            ticks = ticksAFT - ticksB4;
            tt = (double) ticks/freq;
            printf("Task based (+ prio) | %8d | %9.2f | %7.2f \n", nths, tt, tt_seq / tt);
        }

        printf("---------------------------------------------------- \n");
    }

    // Free matrices
    for (i = 0; i < NBLOCKS; i++)
        for (j = 0; j < NBLOCKS; j++)
            free(A[i][j]);
    free(A_flat);

    return 0;
}

