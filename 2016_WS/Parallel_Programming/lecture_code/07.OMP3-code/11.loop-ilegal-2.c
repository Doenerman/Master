#include <stdio.h>
#include <omp.h>

int main ( void )  
{
  int i;
  #pragma omp parallel for
  for( i = 0 ; i < 8; i++ )
  {
    int id = omp_get_thread_num();
    if ( id == 0)
        break;
    printf("Hi! I am thread %d\n", id);
  }

  return 0;
}
