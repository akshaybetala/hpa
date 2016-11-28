#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int liberties2;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int * restrict libs1;
extern int  ml[(19 + 1) *(19 + 1)] ;
extern int liberty_mark;
extern int commonlibs;

void loop()
{
#pragma scop

    for(k = 0; k < liberties2; k++) if(!(board[libs1[k]] == 0 && ml[libs1[k]] != liberty_mark)) commonlibs++;

#pragma endscop
}
