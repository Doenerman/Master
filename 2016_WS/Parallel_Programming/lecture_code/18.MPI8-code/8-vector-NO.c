// mpicc 8-vector-NO.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


int main( int argc, char *argv[] )
{
   int i, j, *local_buffer=NULL, *rec_buffer=NULL;
   int me, nProcs, root;   

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   root = nProcs-1; 

   if( me == root ) 
      { 
         local_buffer = (int *) malloc( 10*nProcs * sizeof(int) );
         for( i=0; i<10*nProcs; i++ ) local_buffer[i]=i;
         
         for( i=0; i<nProcs; i++ )
            if( i != me )
               for( j=0; j<10; j++ )
                  {
                  MPI_Send( &local_buffer[i+j*nProcs], 1, MPI_INT, i, j, MPI_COMM_WORLD );
                  printf( "[%d] sending [%d] to %d\n", me, local_buffer[i+j*nProcs], i );
                  }
         
         free( local_buffer );
      }
   else
      {
         rec_buffer = (int *) malloc( 73 * sizeof(int) );
         MPI_Status status;

         for( j=0; j<10; j++ )
            MPI_Recv( &rec_buffer[j], 73-j, MPI_INT, root, j, MPI_COMM_WORLD, &status );
            
         printf( " [%d] received; buf:\t%d\t%d\t%d\t%d\t...\t%d\n",
                 me, rec_buffer[0], rec_buffer[1], rec_buffer[2], rec_buffer[3], rec_buffer[9] );
         free( rec_buffer );
      }
      
   
   MPI_Finalize();
   return 0;
}


