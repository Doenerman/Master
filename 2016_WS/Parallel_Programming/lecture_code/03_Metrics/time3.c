// gcc time3.c -Wall -o test.x 
// icc time3.c -Wall -o test.x -mkl

// tcsh:  setenv OPENBLAS_NUM_THREADS 1  
// bash:  export OPENBLAS_NUM_THREADS=1

#include <stdlib.h>
#include <stdio.h> 
#include <time.h>

#define get_ticks(var) {					   \
      unsigned int __a, __d;					   \
      asm volatile("rdtsc" : "=a" (__a), "=d" (__d));		   \
      var = ((unsigned long) __a) | (((unsigned long) __d) << 32); \
   } while(0)



int main( int argc, char *argv[] ){
   int m,n,k;
   int i,j,l;
   double *A, *B, *C, *D;
   unsigned long ticksB4, ticksAFT, ticks;  

   if( argc < 4 ){
      printf("3 arguments please!\n");  return(-1);}
   
   m = atof(argv[1]);
   n = atof(argv[2]);
   k = atof(argv[3]);

   A = (double *) malloc( m*k * sizeof(double) );
   B = (double *) malloc( k*n * sizeof(double) );
   C = (double *) malloc( m*n * sizeof(double) );
   D = (double *) malloc( m*n * sizeof(double) );

   srand48( (unsigned)time((time_t *)NULL) ); 
   
   for( i=0; i<m; i++ )
      for( j=0; j<k; j++ ) 
	 A[i+j*m] = drand48();  

   for( i=0; i<k; i++ )
      for( j=0; j<n; j++ ) 
	 B[i+j*k] = drand48();  

   for( i=0; i<m; i++ )
      for( j=0; j<n; j++ ){
	 C[i+j*m] = 0;
	 D[i+j*m] = 0;
      }

   double freq = 2.8e9;
   get_ticks(ticksB4);   
   
   for( i=0; i<m; i++ )
      for( j=0; j<n; j++ )
	 for( l=0; l<k; l++ )
	    C[i+j*m] += A[i+l*m] * B[l+j*k]; 

   get_ticks(ticksAFT); 
   ticks = ticksAFT - ticksB4;
   double rtime = (double) ticks/freq;
   printf(" triple loop:\t%.3g\n", rtime);


   double ops = 2.0*m*n*k;
   printf(" performance:\t%.3g\n", ops/rtime );
   printf(" efficiency:\t%.3g\n", (ops/rtime)/(freq*16) );

   return 0;
}


