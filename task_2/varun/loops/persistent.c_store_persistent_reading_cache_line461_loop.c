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
        if(board[k] == 1 || board[k] == 2 || active[k] != 0) continue;
        if(board[k +(19 + 1)] == 0 && active[k +(19 + 1)] == 2 || board[k - 1] == 0 && active[k - 1] == 2 || board[k -(19 + 1)] == 0 && active[k -(19 + 1)] == 2 || board[k + 1] == 0 && active[k + 1] == 2) active[k] = 3;
    }
    */

    // reversal and merge condition
    for(k = (19 + 1) *(19 + 1) - (19+2) - 1 ; k >= 0; k--)
    {
        int cond = (int) (( !(board[k+21] == 1 || board[k+21] == 2 || active[k+21] != 0) && (board[k + 41] == 0 && active[k+ 41] == 2 || board[k + 20] == 0 && active[k + 20] == 2 || board[k + 1] == 0 && active[k + 1] == 2 || board[k + 22] == 0 && active[k+ 22] == 2)));
        active[k+21] = 3 * cond + active[k+21] * (1 - cond);
    }

#pragma endscop
}
