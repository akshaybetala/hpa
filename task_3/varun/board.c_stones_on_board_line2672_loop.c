#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int white_stones;
extern int black_stones;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(board[pos] == 1) white_stones++;
        else if(board[pos] == 2) black_stones++;
    }

#pragma endscop
}
