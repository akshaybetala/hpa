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

    //loop fission

    int x = (19 + 1) *(19 + 1);
    for(k = 21; k < x; k++)
    {
        safe_move_cache_when[k][0] = - 1;
    }

    for(k = 21; k < x; k++)
    {
        safe_move_cache_when[k][1] = - 1;
    }

#pragma endscop
}
