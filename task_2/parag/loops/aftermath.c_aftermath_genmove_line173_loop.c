#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  distance[20 * 20] ;
extern int  under_control[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(!(board[pos] != 3)) continue;
        else if(distance[pos] == - 1) under_control[pos] = 0;
        else under_control[pos] = 1;
    }

#pragma endscop
}
