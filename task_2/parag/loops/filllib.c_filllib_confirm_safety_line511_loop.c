#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int move;
extern int  delta[8] ;
extern int color;
extern int apos;

void loop()
{
#pragma scop

    for(k = 0; k < 4; k++) if(board[move + delta[k]] == color)
        {
            apos = move + delta[k];
            break;
        }

#pragma endscop
}
