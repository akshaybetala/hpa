#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int max_points;
extern int* restrict points;
extern int move;

void loop()
{
#pragma scop

    for(k = 0; k < max_points; k++) if(points[k] == move) break;

#pragma endscop
}
