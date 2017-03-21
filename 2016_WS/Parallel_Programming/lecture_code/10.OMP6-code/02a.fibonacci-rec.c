#include <stdio.h>
#include <omp.h>

#define N 10

// Assumes n > 0
int fibonacci( int n )
{
    int x, y;

    if (n < 2) 
        return 1;

    x = fibonacci(n-1);
    y = fibonacci(n-2); 

    return x + y;
}

int main ( void )  
{
  int i;
  int fib[N];

  for( i = 0 ; i < N; i++ )
      fib[i] = fibonacci(i);

  // Print out the Fibonacci numbers
  printf("[%d", fib[0]);
  for( i = 1 ; i < N; i++ )
      printf(", %d", fib[i]);
  printf("]\n");

  return 0;
}
