// on RWTH's cluster
// gcc time2.c -Wall -o test.x -L/Users/pauldj/works/libs/lapack-3.5.0/ -llapack -L/opt/local/lib -lopenblas -lgfortran
// icc time2.c -Wall -o test.x -mkl

// laptop
// gcc time2.c -Wall -o test.x -Wall -O2 -L/Users/pauldj/works/libs/OpenBLAS-develop/ -lopenblas

// Multithreading
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
   double ctime;
   unsigned long ticksB4, ticksAFT, ticks; 

   if( argc < 2 ){printf("argument please!\n"); return(-1);}
   else m = atof(argv[1]);
   
   A = (double *) malloc( m*m * sizeof(double) );
   A0= (double *) malloc( m*m * sizeof(double) );

   srand48( (unsigned)time((time_t *)NULL) ); 
   
   for( i=0; i<m; i++ )
      for( j=0; j<=i; j++ ){
	 A[i+j*m] = drand48();
	 A[j+i*m] = 0;
	 if(i == j) A[i+j*m] += m;
	 A0[i+j*m] = A[i+j*m];
	 A0[j+i*m] = A[i+j*m];
      }

   

   // VERSION 1
   /*
   ctime = ((double) clock ())/CLOCKS_PER_SEC;
   get_ticks(ticksB4);   
   
   dpotrf_( "L", &m, A, &m, &info );   

   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" n: %d\t ticks: %.ld\n", m, ticks );
   printf(" n: %d\t clock: %.3g\n", m, 
          (((double) clock ())/CLOCKS_PER_SEC) - ctime);
   */


   
   // VERSION 2
      
   double freq = 2.8e9, rtime;
   ctime = ((double) clock ())/CLOCKS_PER_SEC;
   get_ticks(ticksB4);   
   
   dpotrf_( "L", &m, A, &m, &info );   

   get_ticks(ticksAFT);
   ticks = ticksAFT - ticksB4;
   printf(" n: %d\t ticks: %.ld\n", m, ticks );
   rtime = (double) ticks/freq;
   printf(" n: %d\t sec: %.3g\n", m, (double) rtime );
   printf(" n: %d\t clock: %.3g\n", m, 
          (((double) clock ())/CLOCKS_PER_SEC) - ctime);
   
   
   double ops = (1.0/3.0)*m*m*m;
   printf(" rate (flops/sec): \t%.3lf\n", ops/rtime );
   printf(" efficiency:\t%.3g\n", (ops/rtime)/(freq*16) );

   
   return 0;
}


