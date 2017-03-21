// on RWTH's cluster
// gcc time0.c -Wall -o test.x -L/Users/pauldj/works/libs/lapack-3.5.0/ -llapack -L/opt/local/lib -lopenblas -lgfortran
// icc time0.c -Wall -o test.x -mkl

// laptop
// gcc time0.c -Wall -o test.x -Wall -O2 -L/Users/pauldj/works/libs/OpenBLAS-develop/ -lopenblas

#include <stdlib.h>
#include <stdio.h> 
#include <time.h>

int dpotrf_(char *, int *, double *, int *, int *);

int dgemm_(char *, char *, int *, int *, int *, double *,
	   double *, int *, double *, int *, double *, double *, int *);

double dlange_( char *, int *, int *, double *, int *, double * );

void mat_print( double *A, int n, int m, int ldA, char *text);


int main( int argc, char *argv[] ){
   int i, j, m, info;
   double *A, *A0;

   if(argc < 2){printf("arguments please\n"); return (-1);}
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

   
   dpotrf_( "L", &m, A, &m, &info );   
      

   double one = 1.0, minus = -1.0;
   dgemm_( "N", "T", &m, &m, &m, &one, A, &m, A, &m, &minus, A0, &m ); 
   printf(" norm: %g\n", dlange_( "F", &m, &m, A0, &m, A ) );   
   
   return 0;
}



void mat_print( double *A, int n, int m, int ldA, char *text)
{
   int i, j;
   FILE *output;
   output = stdout;

   fprintf(output, "%s = [ ...\n", text );
   for( i=0; i<n; i++ ) //row
      {
	 for( j=0; j<m; j++ )  //column
	    fprintf(output, "%.15g ", A[i+j*ldA] );
	 fprintf(output, "; ...\n" );
      }
   fprintf(output, "];\n" );

   return;
}
