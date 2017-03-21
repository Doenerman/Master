// mpicc 6b-gather.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main( int argc, char *argv[] )
{
   int i, *local_buffer=NULL, *recv_buffer=NULL;

   MPI_Init(&argc,&argv);
   int me, nProcs;
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   local_buffer = (int *) malloc( 2 * sizeof(int) );
   srand48( (unsigned) me );
   for( i=0; i<2; i++ ) local_buffer[i]=(int) floor(drand48()*100);
   printf( "(%d) local: [%d, %d]\n", me, local_buffer[0], local_buffer[1]);

   if( me == nProcs-1 )
      recv_buffer = (int *) malloc( 2 * nProcs * sizeof(int) );

   MPI_Gather( local_buffer, 2, MPI_INT,
               recv_buffer, 2, MPI_INT, nProcs-1, MPI_COMM_WORLD );
   
   if( me == nProcs-1 )
      for( i=0; i<nProcs*2; i++ ) printf( "(%d)\t\tgathered[%d]=%d\n", me, i, recv_buffer[i]);
   
   MPI_Finalize();
   return 0;
}


