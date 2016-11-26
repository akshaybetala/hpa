#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  mse[20 * 20] ;
extern int other;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++) if(board[pos] != 3 && mse[pos] &&((!(board[pos +(19 + 1)] != 3) || board[pos +(19 + 1)] == other) &&(!(board[pos -(19 + 1)] != 3) || board[pos -(19 + 1)] == other) ||(!(board[pos - 1] != 3) || board[pos - 1] == other) &&(!(board[pos + 1] != 3) || board[pos + 1] == other))) mse[pos] = 0;

#pragma endscop
}
