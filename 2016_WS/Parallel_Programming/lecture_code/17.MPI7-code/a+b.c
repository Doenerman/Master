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

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   if( me==0 && argc < 2 ){ printf("argument please!\n");  return(-1);}
   size = atoi(argv[1]); 

   int *LocalBuffer, *RecvBuffer;
   LocalBuffer = (int *) malloc( size * sizeof(int) );
   RecvBuffer  = (int *) malloc( size * sizeof(int) );
   srand48( me + (unsigned)time((time_t *)NULL) );
   int base = (int) floor(10 * drand48());
   for( i=0; i<size; i++ ) LocalBuffer[i] = base + i; 

   for( i=0; i<size; i++ ) 
      printf( " [%d]  Local[%d]: %d\n", me, i, LocalBuffer[i] );
   
   MPI_Send( LocalBuffer, size, MPI_INT, (me+1)%nProcs, 0, MPI_COMM_WORLD  );
   MPI_Recv( RecvBuffer,  size, MPI_INT, (me+nProcs-1)%nProcs, 0, MPI_COMM_WORLD, &status );

   for( i=0; i<size; i++ ) 
      printf( " [%d]  \t\tRecv[%d]: %d\n", me, i, RecvBuffer[i] );

   /* if( me==0 ) */
   /*    for( i=0; i<size; i++ )  */
   /*       RecvBuffer[i] = RecvBuffer[i] + LocalBuffer[i];  */
   /* if( me==1 ) */
   /*    for( i=0; i<size; i++ )  */
   /*       RecvBuffer[i] = RecvBuffer[i] * LocalBuffer[i];  */
   
   switch( me ){
   case 0:
      for( i=0; i<size; i++ )
         RecvBuffer[i] = RecvBuffer[i] + LocalBuffer[i];
      break;
   case 1:
      for( i=0; i<size; i++ )
         RecvBuffer[i] = RecvBuffer[i] * LocalBuffer[i];
      break;
   default:
      printf( "case does not match\n" );
   }

   for( i=0; i<size; i++ ) 
      printf( " [%d]  \t\tResult[%d]: %d\n", me, i, RecvBuffer[i] );

   free( LocalBuffer );
   free( RecvBuffer );   
   
   MPI_Finalize();
   return 0;
}
