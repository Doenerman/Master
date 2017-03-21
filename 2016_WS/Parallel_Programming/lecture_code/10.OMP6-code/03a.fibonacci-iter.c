#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 10

#define Phi ((1.0+sqrt(5.0)/2.0)

int main ( void )  
{
  int i;
  int fib[N];

  // Initialize
  for( i = 2 ; i < N; i++ )
      fib[i] = 0;
  fib[0] = 1;
  fib[1] = 1;

  // Compute
  #pragma omp parallel
  #pragma omp single
  for( i = 2; i < N; i++ )
      #pragma omp task depend(in:fib[i-2]) depend(out:fib[i]) firstprivate(i)
      fib[i] = fib[i-1] + fib[i-2];

  // Print out the Fibonacci numbers
  printf("[%d", fib[0]);
  for( i = 1 ; i < N; i++ )
      printf(", %d", fib[i]);
  printf("]\n");

  return 0;
}
