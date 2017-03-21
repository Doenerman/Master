// mpicc allgather-bc.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>  // floor

int main( int argc, char *argv[] )
{
   int me, nProcs, root;
   int i, local_size;
   int *local_buffer=NULL, *rec_buffer=NULL;
   
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   if( me == 0 && argc < 2 ){ printf("local_size please!\n");  return -1;}
   local_size = atoi(argv[1]);
   
   // tricky! pay attention to the size
   rec_buffer = (int *) malloc( local_size * nProcs * sizeof(int) );  

   root = nProcs-1;
   if( me == root ){
      local_buffer = (int *) malloc( local_size * nProcs * sizeof(int) );
      srand48( (unsigned) me );
      for( i=0; i<local_size * nProcs ; i++ )
         local_buffer[i]=(int) floor(drand48()*100);

      //      for( i=0; i<local_size * nProcs ; i++ )
      //         printf(" [%d]: buf[%d]= %d\n", me, i, local_buffer[i] );
   }

   // again, pay attention to the position in the rec_buffer -> why?
   MPI_Scatter( local_buffer, local_size, MPI_INT, 
                &rec_buffer[me*local_size], local_size, MPI_INT,
                root, MPI_COMM_WORLD );

   for( i=0; i<local_size; i++ )
      printf(" [%d]:init[%d]= %d\n", me, i, rec_buffer[me*local_size+i] );

   
   // sequence of BCASTs
   for( i=0; i<nProcs; i++ )
      MPI_Bcast( &rec_buffer[i*local_size], local_size, MPI_INT, i, MPI_COMM_WORLD );

   for( i=0; i<local_size * nProcs; i++ )
      printf(" [%d]: \t\trecv[%d]= %d\n", me, i, rec_buffer[i] );
   
   MPI_Finalize();
   return 0;
}


