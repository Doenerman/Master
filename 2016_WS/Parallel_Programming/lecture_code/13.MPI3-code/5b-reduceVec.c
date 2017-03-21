#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   int buffer[2] = {1,2}, result[2] = {0,0};

   printf(" [%d]\t buffer: [%d,%d]\n", me, buffer[0], buffer[1] );
   MPI_Reduce( buffer, result, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

   if( me == 0 )
      printf(" [%d]\t Reduction: [%d,%d]\n", me, result[0], result[1] );

   MPI_Finalize();
   return 0;
}


