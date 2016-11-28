#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern int  cached_board[20 * 20] ;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int board_was_cached;

void loop()
{
#pragma scop
/*
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++)
    {
        if(cached_board[ii] != board[ii])
        {
            cached_board[ii] = board[ii];
            board_was_cached = 0;
        }
    }
*/

//loop invariant code model

    int x = (19 + 1) *(19 + 1);
    for(ii = 19 + 2; ii <x; ii++)
    {
        if(cached_board[ii] != board[ii])
        {
            board_was_cached = 0;
        }
    }
    
    for(ii = 19 + 2; ii <x; ii++)
    {
            board_was_cached = 0;
    }

    

#pragma endscop
}
