#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
   int me=0, nProcs, err, n=512, *A;
   
   MPI_Init(&argc, &argv);
   
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   A = (int *) malloc( n * n * sizeof(int) );
   
   if( me == 0 ){
      if(argc <= 3){ printf(" Pass me 3 arguments!\n"); return(-1);}

      if(argc > 3) initMatrix( A, argv[1], argv[2], argv[3] );
      
      err = MPI_Bcast(A, n*n, MPI_INT, 0, MPI_COMM_WORLD);
      if (err != MPI_SUCCESS) printf(" [%d] BCAST ERROR\n", me );     
   }
   
   /*
     ...
   */
   
   MPI_Finalize();
   return 0;
}


