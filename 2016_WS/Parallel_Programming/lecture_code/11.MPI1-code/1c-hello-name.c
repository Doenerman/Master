// mpicc 1c-hello-name.c -Wall -o test.x

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[] )
{
   char name[100];
   int nameLength;
   MPI_Init(&argc,&argv);

   MPI_Get_processor_name(name, &nameLength);
      
   printf("Proc name:\t%s\n", name);

   MPI_Finalize();
   return 0;
}


