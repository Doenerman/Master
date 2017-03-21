// mpicc 8-vector-type.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


int main( int argc, char *argv[] )
{
   int i, *local_buffer=NULL, *rec_buffer=NULL;
   int me, nProcs, root;   

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   root = nProcs-1; 

   // new datatype
   MPI_Datatype new_type;
   MPI_Type_vector( 10, 1, nProcs, MPI_INT, &new_type );
   MPI_Type_commit( &new_type );
   
   if( me == root ){ 
      local_buffer = (int *) malloc( 10*nProcs * sizeof(int) );
      for( i=0; i<10*nProcs; i++ ) local_buffer[i]=i;
            
      for( i=0; i<nProcs; i++ )
         if( i != root )
            MPI_Ssend( &local_buffer[i], 1, new_type, i, i, MPI_COMM_WORLD );
      
      free( local_buffer );
   }
   else{
      //      rec_buffer = (int *) malloc( 73 * sizeof(int) );
      rec_buffer = (new_type *) malloc( sizeof(new_type) );
      MPI_Status status;
      int size;
      
      //MPI_Recv( rec_buffer, 73, MPI_INT, root, me, MPI_COMM_WORLD, &status );
      //MPI_Get_count( &status, MPI_INT, &size );

      // buffer size!!!!
      MPI_Recv( rec_buffer, 1, new_type, root, me, MPI_COMM_WORLD, &status );
      MPI_Get_count( &status, new_type, &size );
      
      printf( "[%d] I received %d items\n", me, size );
      printf( "[%d]\t\t\t%d\t%d\t%d...\t%d \n", me,
              rec_buffer[0], rec_buffer[nProcs], rec_buffer[2*nProcs], rec_buffer[9*nProcs] );
      
      free( rec_buffer );
   }

   MPI_Type_free ( &new_type );
   MPI_Finalize();
   return 0;
}


