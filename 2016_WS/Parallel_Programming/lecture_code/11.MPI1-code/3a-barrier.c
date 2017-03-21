#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   
   printf(" [%d]\t before barrier\n", me );
   MPI_Barrier(MPI_COMM_WORLD);
   printf(" [%d]\t\t\t I made it through the barrier!\n", me );

   MPI_Finalize();
   return 0;
}


