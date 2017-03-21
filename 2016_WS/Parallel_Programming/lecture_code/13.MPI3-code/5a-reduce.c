// mpicc 5a-reduce.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   // Goal: find the maximum of a bunch of random numbers, each sitting in a
   // different process
   
   srand48( me + (unsigned)time((time_t *)NULL) );  
   double buffer = drand48(), result=0; 

   printf(" [%d]\t my-buffer: %.15f\n", me, buffer );
   MPI_Reduce( &buffer, &result, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );

   if( me == 0 )
      printf(" [%d]\t\t\t Reduction: %.15f\n", me, result );

   MPI_Finalize();
   return 0;
}


