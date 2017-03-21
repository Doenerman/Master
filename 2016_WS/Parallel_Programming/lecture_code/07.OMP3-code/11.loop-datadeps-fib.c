#include <stdio.h>
#include <omp.h>

#define N 10

int main ( void )  
{
  int i;
  int fib[N];

  for( i = 2 ; i < N; i++ )
      fib[i] = 0;

  fib[0] = 1;
  fib[1] = 1;
  // 4 iters for th0, 4 for th1
  #pragma omp parallel for num_threads(2)
  for( i = 2 ; i < N; i++ )
      fib[i] = fib[i-1] + fib[i-2];

  printf("[");
  for( i = 0 ; i < N; i++ )
      printf("%d, ", fib[i]);
  printf("]\n");

  return 0;
}
