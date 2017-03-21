// mpicc 9-COMM-split.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main( int argc, char *argv[] )
{
   int me_WORLD, nP_WORLD;   

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me_WORLD );
   MPI_Comm_size( MPI_COMM_WORLD, &nP_WORLD );

   if( nP_WORLD % 4 != 0 ){
      printf( "[%d] nP is not a multiple of 4 -- try again\n", me_WORLD );
      return -1;
   }

   int color, key;
   MPI_Comm COMM_row;
   color = me_WORLD / 4;  // We assume to have rx4 processes
   key   = me_WORLD;

   // row communicator 
   MPI_Comm_split( MPI_COMM_WORLD, color, key, &COMM_row );

   int me_ROW, nP_ROW;
   MPI_Comm_rank( COMM_row, &me_ROW );
   MPI_Comm_size( COMM_row, &nP_ROW );
   printf("[%d]\tCOMM_row rank: %d (%d)\n", me_WORLD, me_ROW, nP_ROW );




   // column communicator    
   MPI_Comm COMM_col;
   int me_COL, nP_COL;
   MPI_Comm_split( MPI_COMM_WORLD, me_WORLD%4, key, &COMM_col );

   MPI_Comm_rank( COMM_col, &me_COL );
   MPI_Comm_size( COMM_col, &nP_COL );
   printf("[%d]\t\t\tCOMM_col rank: %d (%d)\n", me_WORLD, me_COL, nP_COL );
   
   MPI_Comm_free( &COMM_row );
   MPI_Comm_free( &COMM_col );
   MPI_Finalize();
   return 0;
}


