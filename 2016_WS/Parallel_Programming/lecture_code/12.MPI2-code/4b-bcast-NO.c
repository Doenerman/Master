#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs, err=0;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   int buffer = me;  // try with long buffer

   /* init */
   if( me == 0 ){
      if( argc < 2 ){ printf("argument please!\n");  return(-1);}
      buffer = atoi(argv[1]);
   }

   /* BCAST */
   printf(" [%d] buffer: %d\n", me, buffer );
   if( me%2==0 ){
      err = MPI_Bcast( &buffer, 1, MPI_INT, 0, MPI_COMM_WORLD );
      if( err != MPI_SUCCESS ) printf(" [%d] BCAST ERROR\n", me );
   }
   printf(" [%d]\t\t\t---> buffer: %d\n", me, buffer );

   /*
     ...
   */

   // MPI_Barrier( MPI_COMM_WORLD );
   
   MPI_Finalize();
   return 0;
}


