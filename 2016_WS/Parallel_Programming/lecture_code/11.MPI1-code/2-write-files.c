#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

int main( int argc, char *argv[] )
{
   int rank, nProcs;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &nProcs );
   //   printf("I am process %d (%d)\n", rank, nProcs);

   char filename[20] = "output", myrank[5];
   sprintf(myrank, "%d", rank);
   strcat(filename, myrank);

   printf(" filename: %s\n", filename );

   FILE *output;
   output = fopen(filename, "w");

   if(output == NULL) {
      printf("Could not open file 'output-file.ext'");
      return( 1 );
   }

   fprintf(output, "I am process %d (%d)\n", rank, nProcs);
   
   MPI_Finalize();
   return 0;
}


