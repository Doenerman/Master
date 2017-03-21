#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 1000

int main( void )
{
    float read_buff[2][N];
    float write_buff[2][N];

    int cur_read = 0, next_read = 1;
    int cur_write = 0, prev_write = 1;
    int iter = 0, niters = 5;
    int tmp;

    // Read in read_buf[cur_read]
    sleep( 1 );
    #pragma omp parallel 
    {
        while (iter < niters)
        {
            // First and third sections could be merged
            #pragma omp sections
            {
                #pragma omp section
                // Read in read_buf[next_read] (not for the last iteration)
                if (iter < niters-1)
                    sleep( 1 );
                #pragma omp section
                // write_buff[cur_write] = compute( read_buff[cur_read] )
                sleep( 6 ); // -> this can easily be a parallel for
                #pragma omp section
                // write write_buff[prev_write] (not for the first iteration)
                if ( iter > 0 )
                    sleep( 1 );
            }
            // Increase iteration number and swap indices to buffers
            #pragma omp single
            {
                iter++;
                tmp = cur_read;  cur_read = next_read;  next_read = tmp;
                tmp = cur_write;  cur_write = prev_write;  prev_write = tmp;
            }
        }
        #pragma omp single
        // write write_buff[prev_write]
        sleep( 1 );
    }

    return 0;
}
