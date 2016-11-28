#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  current_board[20 * 20] ;
extern int cached_board;

void loop()
{
#pragma scop
/*
    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(board[pos] != 3 && board[pos] != current_board[pos])
        {
            current_board[pos] = board[pos];
            cached_board = 0;
        }
    }
*/
	int x = (19 + 1) *(19 + 1);
	for(pos = 19 + 2; pos <x; pos++)
    {
        if(board[pos] != 3 && board[pos] != current_board[pos])
        {
            current_board[pos] = board[pos];
            cached_board = 0;
        }
    }

#pragma endscop
}
