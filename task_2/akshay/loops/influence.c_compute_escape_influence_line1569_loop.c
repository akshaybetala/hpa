#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  escape_value[(19 + 1) *(19 + 1)] ;
extern char  escape_values[20 * 20][2] ;
extern int cache_number;

void loop()
{
#pragma scop
/*
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) if(board[ii] != 3) escape_value[ii] = escape_values[ii][cache_number];
*/

// lool invariant variable model
	int x = (19 + 1) *(19 + 1);
	for(ii = 19 + 2; ii <x; ii++){
		int cond = (board[ii] == 3);
		escape_value[ii] *= 1*cond +  (1-cond)*escape_values[ii][cache_number];
	}

#pragma endscop
}
