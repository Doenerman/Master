// mpicc 9a-all-send.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main( int argc, char *argv[] )
{
   int i, size=6, me, nProcs;
   MPI_Status status;
   MPI_Request requestS, requestR;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   if( me==0 && argc < 2 ){ printf("argument please!\n");  return(-1);}
   size = atoi(argv[1]); 

   int *LocalBuffer, *RecvBuffer, *output;
   LocalBuffer = (int *) malloc( size * sizeof(int) );
   RecvBuffer  = (int *) malloc( size * sizeof(int) );
   output      = (int *) malloc( size * sizeof(int) );
   srand48( me + (unsigned)time((time_t *)NULL) );
   int base = (int) floor(10 * drand48());
   for( i=0; i<size; i++ ) LocalBuffer[i] = base + i; 

   for( i=0; i<size; i++ ) 
      printf( " [%d]  Local[%d]: %d\n", me, i, LocalBuffer[i] );

   double MPItime;
   MPI_Barrier( MPI_COMM_WORLD );
   MPItime = MPI_Wtime();


   // Solution #1
   /*
   if( me%nProcs == 0 ){
      MPI_Ssend( LocalBuffer, size, MPI_INT, 1, 0, MPI_COMM_WORLD  );
      MPI_Recv ( RecvBuffer,  size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status );
   };
   if( me%nProcs == 1 ){
      MPI_Recv ( RecvBuffer,  size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );
      MPI_Ssend( LocalBuffer, size, MPI_INT, 0, 0, MPI_COMM_WORLD  );
   } 
   for( i=0; i<size; i++ )
      output[i] = LocalBuffer[i] * LocalBuffer[i];
   */










   





   
   
   // Solution #2
   /*
   MPI_Isend( LocalBuffer, size, MPI_INT, (me+1)%nProcs, 0, MPI_COMM_WORLD, &requestS );
   for( i=0; i<size; i++ )
      output[i] = LocalBuffer[i] * LocalBuffer[i]; 
   MPI_Recv ( RecvBuffer,  size, MPI_INT, (me+1)%nProcs, 0, MPI_COMM_WORLD, &status );   
   */




















   
   

   // Solution #3

   MPI_Isend( LocalBuffer, size, MPI_INT, (me+1)%nProcs, 0, MPI_COMM_WORLD, &requestS );
   MPI_Irecv( RecvBuffer,  size, MPI_INT, (me+1)%nProcs, 0, MPI_COMM_WORLD, &requestR );   
   for( i=0; i<size; i++ )
      output[i] = LocalBuffer[i] * LocalBuffer[i]; 
   MPI_Wait( &requestR, &status );

  

   for( i=0; i<size; i++ ) 
      output[i] = RecvBuffer[i] + output[i]; 

   for( i=0; i<size; i++ ) 
      printf( " [%d]  \t\tResult[%d]: %d\n", me, i, output[i] );

   MPI_Barrier( MPI_COMM_WORLD );
   MPItime = MPI_Wtime() - MPItime;
   printf( " [%d]  \t\ttime: %lf\n", me, MPItime );
      
   free( LocalBuffer );
   free( RecvBuffer );
   free( output );
   
   MPI_Finalize();
   return 0;
}
