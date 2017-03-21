#include <stdio.h>
#include <omp.h>

int main ( void )  
{
  #pragma omp parallel for
  for( ; ; )
  {
    int id = omp_get_thread_num();
    printf("Hi! I am thread %d\n", id);
  }

  return 0;
}
