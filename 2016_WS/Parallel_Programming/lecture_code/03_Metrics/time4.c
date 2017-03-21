// LAPACK: -L/Users/pauldj/works/libs/lapack-3.5.0/  -llapack  -lgfortran
// BLAS:   -L/opt/local/lib -lopenblas

// gcc time4.c -Wall -o test.x -L/Users/pauldj/works/libs/lapack-3.5.0/ -llapack -L/opt/local/lib -lopenblas -lgfortran
// icc time4.c -Wall -o test.x -mkl

// tcsh:  setenv OPENBLAS_NUM_THREADS 1  
// bash:  export OPENBLAS_NUM_THREADS=1

#include <stdlib.h>
#include <stdio.h> 
#include <time.h>

int dpotrf_(char *, int *, double *, int *, int *);

int dgemm_(char *, char *, int *, int *, int *, double *,
	   double *, int *, double *, int *, double *, double *, int *);

double dlange_( char *, int *, int *, double *, int *, double * );


#define get_ticks(var) {					   \
      unsigned int __a, __d;					   \
      asm volatile("rdtsc" : "=a" (__a), "=d" (__d));		   \
      var = ((unsigned long) __a) | (((unsigned long) __d) << 32); \
   } while(0)



int main( int argc, char *argv[] ){
   int i, j, m, info;
   double *A, *A0;
   unsigned long ticksB4, ticksAFT, ticks;
   double freq = 2.8e9;  

   /* --- malloc ---------------------------------- */ 
   
   get_ticks(ticksB4);
   if( argc < 2 ){printf("argument please!\n"); return(-1);}
   m = atof(argv[1]);

   A = (double *) malloc( m*m * sizeof(double) );
   A0= (double *) malloc( m*m * sizeof(double) );
   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" malloc(%d):\t%.3g\n", m, (double) ticks/freq );

   /* --- init ---------------------------------- */ 

   get_ticks(ticksB4);   
   srand48( (unsigned)time((time_t *)NULL) ); 
   for( i=0; i<m; i++ )
      for( j=0; j<=i; j++ ){
	 A[i+j*m] = drand48();
	 A[j+i*m] = 0;
	 if(i == j) A[i+j*m] += m;
	 A0[i+j*m] = A[i+j*m];
	 A0[j+i*m] = A[i+j*m];
      }
   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" init(%d):\t%.3g\n", m, (double) ticks/freq );

   /* --- compute ---------------------------------- */ 
   
   get_ticks(ticksB4);      
   dpotrf_( "L", &m, A, &m, &info );   
   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" comp(%d):\t%.3g\n", m, (double) ticks/freq );

   /* --- test ---------------------------------- */ 

   get_ticks(ticksB4);      
   double one = 1.0, minus = -1.0;
   dgemm_( "N", "T", &m, &m, &m, &one, A, &m, A, &m, &minus, A0, &m ); 
   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" test(%d):\t%.3g\n", m, (double) ticks/freq );
   double ops = 2.0*m*m*m;
   printf(" perf(GEMM):\t%.3g\n",  ops/(ticks/freq) );
   printf("  eff(GEMM):\t%.3g\n", (ops/(ticks/freq))/(freq*16) );
   printf("\n norm:\t\t%g\n", dlange_( "F", &m, &m, A0, &m, A ) );   
   
   
   return 0;
}


