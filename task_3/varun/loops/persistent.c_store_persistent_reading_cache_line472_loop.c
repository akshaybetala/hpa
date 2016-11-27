#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  active[20 * 20] ;

void loop()
{
#pragma scop

    /*
    for(k = 19 + 2; k <(19 + 1) *(19 + 1); k++)
    {
        if(!(board[k] != 3)) continue;
        if(active[k] != 0) continue;
        if(board[k +(19 + 1)] != 3 && active[k +(19 + 1)] > 0 && active[k +(19 + 1)] < 4 || board[k - 1] != 3 && active[k - 1] > 0 && active[k - 1] < 4 || board[k -(19 + 1)] != 3 && active[k -(19 + 1)] > 0 && active[k -(19 + 1)] < 4 || board[k + 1] != 3 && active[k + 1] > 0 && active[k + 1] < 4) active[k] = 4;
    }
    */
    //normalise and merge condition
    for(k = 0 ; k < 379; k++)
    {

        if( (board[k + 21] != 3) && !(active[k + 21] != 0) && (board[k + 41] != 3 && active[k + 41] > 0 && active[k+ 41] < 4 || board[k + 20] != 3 && active[k + 20] > 0 && active[k + 20] < 4 || board[k+ 1] != 3 && active[k + 1] > 0 && active[k + 1] < 4 || board[k + 22] != 3 && active[k + 22] > 0 && active[k + 22] < 4)) active[k + 21] = 4;
    }

#pragma endscop
}
