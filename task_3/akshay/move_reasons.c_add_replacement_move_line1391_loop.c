#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  replacement_map[(19 + 1) *(19 + 1)] ;
extern int from;

void loop()
{
#pragma scop

	int x = (19 + 1) *(19 + 1);
    for(pos = 19 + 2; pos <x; pos++)
    {
        if(board[pos] != 3 && replacement_map[pos] == from) replacement_map[pos] = replacement_map[from];
    }

#pragma endscop
}
