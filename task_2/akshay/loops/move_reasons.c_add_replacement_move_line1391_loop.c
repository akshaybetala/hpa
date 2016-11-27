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
/*
    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(board[pos] != 3 && replacement_map[pos] == from) replacement_map[pos] = replacement_map[from];
    }
*/	
	int rf;
	if(from < 400)
		rf = replacement_map[from];
	    for(pos = 19 + 2; pos <400; pos++)
	    {
	        if(board[pos] != 3 && replacement_map[pos] == from) replacement_map[pos] = rf;
	    }

#pragma endscop
}
