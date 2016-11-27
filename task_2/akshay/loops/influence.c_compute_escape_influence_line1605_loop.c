#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  escape_values[20 * 20][2] ;
extern int cache_number;
extern char  escape_value[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop
/*
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) if(board[ii] != 3) escape_values[ii][cache_number] = escape_value[ii];
*/

//loop reversal
	int x = (19 + 1)*(19 + 1);
	for(ii = 19 + 2; ii <x; ii++){ 
		if(board[ii] == 3){
			continue;
		}
		
		escape_values[ii][cache_number] = escape_value[ii];
	}

#pragma endscop
}
