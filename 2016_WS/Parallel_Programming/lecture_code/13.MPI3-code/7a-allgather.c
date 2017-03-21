// mpicc 7a-allgather.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main( int argc, char *argv[] )
{
   int i, *local_buffer=NULL, *rec_buffer=NULL;
   double starttime, endtime;
   
   MPI_Init(&argc,&argv);
   int me, nProcs;
   MPI_Comm_rank( MPI_COMM_WORLD, &me );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );

   local_buffer = (int *) malloc( 2 * sizeof(int) );
   srand48( (unsigned) me );
   for( i=0; i<2; i++ ) local_buffer[i]=(int) floor(drand48()*100);
   printf( "(%d) local: [%d, %d]\n", me, local_buffer[0], local_buffer[1]);


   rec_buffer = (int *) malloc( 2 * nProcs * sizeof(int) );
   starttime = MPI_Wtime();
   MPI_Allgather( local_buffer, 2, MPI_INT, rec_buffer, 2, MPI_INT, MPI_COMM_WORLD );
   endtime = MPI_Wtime();
   printf("[%d] \t\t\tAllgather time: %f secs\n", me, endtime-starttime);   
   // for( i=0; i<nProcs*2; i++ )
   //   printf( "(%d) \t\t\tgathered[%d]=%d\n", me, i, rec_buffer[i]);

   // TODO: reduce timings
   
   // if(me==0) printf(" Tick resolution: %.5g secs\n", MPI_Wtick());
   
   MPI_Finalize();
   return 0;
}


