#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  active[20 * 20] ;
extern char  goal[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++) if(board[pos] != 3) active[pos] =(goal[pos] != 0);

#pragma endscop
}
