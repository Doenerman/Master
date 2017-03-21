// mpicc 8-scatter-reduce.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs, local=2, i;
   double *buffer=NULL, *recvBuffer=NULL, result=0;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   if( me == 0 && argc < 2 ){ printf("argument please!\n");  return(-1);}
   local = atoi(argv[1]); // size of the local array
   
   if( me == nProcs-1 ){
      //srand48( (unsigned)time((time_t *)NULL) );
      srand48( (unsigned) me );

      buffer = (double *) malloc( local * nProcs * sizeof(double) );
      for( i=0; i<nProcs*local; i++ ) buffer[i]=drand48();
      //for( i=0; i<nProcs*local; i++ ) printf( "(%d) source[%d]=%g\n", me, i, buffer[i]);
   }

   recvBuffer = (double *) malloc( local * sizeof(double) );
   MPI_Scatter( buffer, local, MPI_DOUBLE,
                recvBuffer, local, MPI_DOUBLE, nProcs-1, MPI_COMM_WORLD );
   // for( i=0; i<local; i++ )
   //   printf( "(%d) \t\treceived[%d]=%g\n", me, i, recvBuffer[i]);
   
   double localSum=0;
   for( i=0; i<local; i++ ) localSum += recvBuffer[i];
   MPI_Reduce( &localSum, &result, 1, MPI_DOUBLE, MPI_SUM, nProcs-1, MPI_COMM_WORLD );
      
   if( me == nProcs-1 ){
      double tot = 0;
      for( i=0; i<nProcs*local; i++ ) tot+=buffer[i];
      printf( "(%d) \t\t\tseqRes:%.16g\n", me, tot );
      printf( "(%d) \t\t\tparRes:%.16g\n", me, result );
   }
      
   MPI_Finalize();
   return 0;
}


