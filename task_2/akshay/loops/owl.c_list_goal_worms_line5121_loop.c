#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int  goal_worm[15] ;

void loop()
{
#pragma scop

    for(k = 0; k < 15; k++) goal_worm[k] = 0;

#pragma endscop
}
