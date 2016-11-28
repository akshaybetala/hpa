#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int pos;
extern int  delta[8] ;
extern int other;
extern int  lively[(19 + 1) *(19 + 1)] ;
extern int all_lively;

void loop()
{
#pragma scop

//    for(k = 0; k < 4; k++) if(board[pos + delta[k]] == other && !lively[pos + delta[k]]) all_lively = 0;
	int x = 0;
	int c = 0 ;
	for(k = 0; k < 4; k++){ 
		x = pos + delta[k];
		c += (board[x] == other && !lively[x]);
	}
	if(c > 0)
		all_lively = 0;

#pragma endscop
}
