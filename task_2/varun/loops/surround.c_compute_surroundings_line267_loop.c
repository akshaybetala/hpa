#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int dpos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  mn[20 * 20] ;
extern int k;
extern int  delta[8] ;

void loop()
{
#pragma scop

    for(dpos = 19 + 2; dpos <(19 + 1) *(19 + 1); dpos++) if(board[dpos] != 3 && mn[dpos] == 1) for(k = 0; k < 4; k++) if(board[dpos + delta[k]] != 3 && !mn[dpos + delta[k]]) mn[dpos + delta[k]] = 2;

#pragma endscop
}
