// mpicc 8-vector-type.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


int main( int argc, char *argv[] )
{
   int i, j, *root_Matrix=NULL, *rec_Matrix=NULL;
   int me, nProcs, root, m, n;   

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   root = nProcs-1; 
   m = 4;  n = 7;

   // new datatype
   MPI_Datatype new_type;
   MPI_Type_vector( 3, 2, m, MPI_INT, &new_type );
   MPI_Type_commit( &new_type );
   
   if( me == root ){
      root_Matrix = (int *) malloc( m*n * sizeof(int) );
      for( i=0; i<m*n; i++ ) root_Matrix[i]=i;

      printf( "[%d]  root_Matrix\n", me ); 
      for( i=0; i<m; i++ ){
         printf( "[%d]", me ); 
         for( j=0; j<n; j++ )
            printf( "  %3d", root_Matrix[j*m + i] );
         printf( "\n" ); 
      }
            
      MPI_Ssend( &root_Matrix[9], 1, new_type, root-1, 123, MPI_COMM_WORLD );
      
      free( root_Matrix );
   };

   if( me == root-1 ){
      MPI_Status status;
      int size;
      
      rec_Matrix = (int *) malloc( m*n * sizeof(int) );
      for( i=0; i<m*n; i++ ) rec_Matrix[i]=1;

      printf( "[%d]  rec_Matrix\n", me ); 
      for( i=0; i<m; i++ ){
         printf( "[%d]", me ); 
         for( j=0; j<n; j++ )
            printf( "  %3d", rec_Matrix[j*m + i] );
         printf( "\n" ); 
      }


      MPI_Recv( &rec_Matrix[2], m*n, new_type, root, 123, MPI_COMM_WORLD, &status );
      MPI_Get_count( &status, new_type, &size );
      printf( "[%d] I received %d items\n", me, size );

      
      printf( "[%d]  rec_Matrix\n", me ); 
      for( i=0; i<m; i++ ){
         printf( "[%d]", me ); 
         for( j=0; j<n; j++ )
            printf( "  %3d", rec_Matrix[j*m + i] );
         printf( "\n" ); 
      }

      free( rec_Matrix );
   }

   MPI_Type_free ( &new_type );
   MPI_Finalize();
   return 0;
}


