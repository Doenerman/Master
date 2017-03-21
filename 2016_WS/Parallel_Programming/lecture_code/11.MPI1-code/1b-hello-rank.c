// mpicc 1b-hello-rank.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main( int argc, char *argv[] )
{
   int rank, nProcs;
   
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   printf("Proc num:\t%d/%d\n", rank, nProcs);

   MPI_Finalize();
   return 0;
}


