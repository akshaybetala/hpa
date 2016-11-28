#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  mn[20 * 20] ;
extern int * restrict surround_size;

void loop()
{
#pragma scop

	/*
    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++) if(board[pos] != 3 && mn[pos] == 1) ( *surround_size)++;

	*/

    //merging condition with computation

for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++) {
	*surround_size += (int) (board[pos] != 3 && mn[pos] == 1);
}

#pragma endscop
}

