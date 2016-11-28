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
    for(k = 19 + 2; k <(19 + 1) *(19 + 1); k++)
    {
        // if(!(board[k] != 3)) continue;
        // if(active[k] != 0) continue;
        // if(board[k +(19 + 1)] != 3 && active[k +(19 + 1)] > 0 && active[k +(19 + 1)] < 4 || board[k - 1] != 3 && active[k - 1] > 0 && active[k - 1] < 4 || board[k -(19 + 1)] != 3 && active[k -(19 + 1)] > 0 && active[k -(19 + 1)] < 4 || board[k + 1] != 3 && active[k + 1] > 0 && active[k + 1] < 4) active[k] = 4;
        int cond = (int) ((!(board[k] != 3)) && (active[k] != 0) && (board[k +(19 + 1)] != 3 && active[k +(19 + 1)] > 0 && active[k +(19 + 1)] < 4 || board[k - 1] != 3 && active[k - 1] > 0 && active[k - 1] < 4 || board[k -(19 + 1)] != 3 && active[k -(19 + 1)] > 0 && active[k -(19 + 1)] < 4 || board[k + 1] != 3 && active[k + 1] > 0 && active[k + 1] < 4));
        active[k] = 4 * cond + active[k] * (1 - cond);
    }

#pragma endscop
}
