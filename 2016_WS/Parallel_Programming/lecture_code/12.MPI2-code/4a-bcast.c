#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   int buffer = me;

   /* init */
   if( me == 0 ){
      if( argc < 2 ){ printf("argument please!\n");  return(-1);}
      buffer = atoi(argv[1]);
   }
   
   /* BCAST */
   printf(" [%d]\t before bcast: %d\n", me, buffer );
   MPI_Bcast( &buffer, 1, MPI_INT, 0, MPI_COMM_WORLD );
   printf(" [%d]\t\t\t after bcast:  %d\n", me, buffer );

   MPI_Finalize();
   return 0;
}


