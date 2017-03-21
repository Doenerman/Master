#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define N 10

typedef struct {
    int x;
    int y;
} point;

point max_bbox_comb( point omp_in, point omp_out )
{
    omp_out.x = omp_out.x > omp_in.x ? omp_out.x : omp_in.x;
    omp_out.y = omp_out.y > omp_in.y ? omp_out.y : omp_in.y;
    return omp_out;
}

point max_bbox_init( void )
{
    point omp_priv;
    omp_priv.x = INT_MIN;
    omp_priv.y = INT_MIN;
    return omp_priv;
}

point min_bbox_comb( point omp_in, point omp_out )
{
    omp_out.x = omp_out.x < omp_in.x ? omp_out.x : omp_in.x;
    omp_out.y = omp_out.y < omp_in.y ? omp_out.y : omp_in.y;
    return omp_out;
}

point min_bbox_init( void )
{
    point omp_priv;
    omp_priv.x = INT_MAX;
    omp_priv.y = INT_MAX;
    return omp_priv;
}

#pragma omp declare \
    reduction(max_bbox: point : omp_out=max_bbox_comb(omp_in, omp_out)) \
    initializer(omp_priv=max_bbox_init())

#pragma omp declare \
    reduction(min_bbox: point : omp_out=min_bbox_comb(omp_in, omp_out)) \
    initializer(omp_priv=min_bbox_init())

int main( void )
{
    int i;
    point points[N];
    point max_point = max_bbox_init();
    point min_point = min_bbox_init();

    for (i = 0; i < N; i++) {
        points[i].x = rand() % 50;
        points[i].y = rand() % 50;
    }
    
    // Checking
    printf("[(%d,%d)", points[0].x, points[1].y);
    for (i = 0; i < N; i++)
        printf(", (%d,%d)", points[i].x, points[i].y);
    printf("]\n");

    #pragma omp parallel for reduction(max_bbox:max_point) reduction(min_bbox:min_point)
    for (i = 0; i < N; i++) {
        max_point = max_bbox_comb( max_point, points[i] );
        min_point = min_bbox_comb( min_point, points[i] );
    }

    // Checking
    printf("Bounding box:\n");
    printf("\tMin: (%d, %d)\n", min_point.x, min_point.y);
    printf("\tMax: (%d, %d)\n", max_point.x, max_point.y);

    return 0;
}
