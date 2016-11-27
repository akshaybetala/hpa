#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int  safe_move_cache_when[(19 + 1) *(19 + 1)][2] ;

void loop()
{
#pragma scop

	/*
    for(k = 19 + 2; k <(19 + 1) *(19 + 1); k++)
    {
        safe_move_cache_when[k][0] = - 1;
        safe_move_cache_when[k][1] = - 1;
    }
    */

    //treating two-d matrix as one-d matrix

    int x = (19 + 1) *(19 + 1)*2;
    int * p = (int *)&safe_move_cache_when;
    for(k = 21; k < x; k++)
    {
       p[k] = - 1;
    }


#pragma endscop
}
