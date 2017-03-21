// mpicc 6a-scatter.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs, n=2, i, *buffer=NULL, *recbuffer=NULL;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   if( me == 0 ){
      buffer = (int *) malloc( n * nProcs * sizeof(int) );
      for( i=0; i<nProcs; i++ ) {
         buffer[n*i]=1000*i+i;
         buffer[n*i+1]=1000*i+i+1;
      }
      for( i=0; i<nProcs*n; i++ )
         printf( "(%d) source[%d]=%d\n", me, i, buffer[i]);
   }

   recbuffer = (int *) malloc( n * sizeof(int) );

   MPI_Scatter( buffer, n, MPI_INT,
                recbuffer, n, MPI_INT, 0, MPI_COMM_WORLD );

   for( i=0; i<n; i++ )
      printf( "(%d) \t\t\treceived[%d]=%d\n", me, i, recbuffer[i]);

   MPI_Finalize();
   return 0;
}


