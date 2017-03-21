// mpicc 6b-all-send.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main( int argc, char *argv[] )
{
   int i, size=1, me, nProcs;
   int *data_OUT, *data_IN;
   MPI_Status status;
   
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   while( 1 ){ 
      size     = size*2; if( me == 0 ) printf( "size=%d\n", size ); 
      data_IN  = (int *) malloc( size * sizeof(int) );
      data_OUT = (int *) malloc( size * sizeof(int) );
      srand48( (unsigned) me );

      for( i=0; i<size; i++ )
      data_OUT[i]=(int) floor(drand48()*100);

      // definite deadlock
      MPI_Ssend( data_OUT, size, MPI_INT, (me+nProcs-1)%nProcs, 0, MPI_COMM_WORLD  );
      MPI_Recv ( data_IN,  size, MPI_INT, (me+1)%nProcs,        0, MPI_COMM_WORLD, &status );
      printf( " [%d] received(%d)!\n", me, size );
   
      free( data_IN );
      free( data_OUT );
   }
   
   MPI_Finalize();
   return 0;
}
