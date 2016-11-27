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

    //loop normalisation and merge condition
    for(k = (19 + 1) *(19 + 1) - (19+2) - 1 ; k >= 0; k--)
    {
        if( !(board[k+(19+2)] == 1 || board[k+(19+2)] == 2 || active[k+(19+2)] != 0) && (board[k + (19+2) +(19 + 1)] == 0 && active[k+ (19+2) +(19 + 1)] == 2 || board[k + (19+2) - 1] == 0 && active[k + (19+2) - 1] == 2 || board[k + (19+2) -(19 + 1)] == 0 && active[k + (19+2) -(19 + 1)] == 2 || board[k +(19+2)+ 1] == 0 && active[k+ (19+2) + 1] == 2)) active[k+(19+2)] = 3;
    }

#pragma endscop
}
