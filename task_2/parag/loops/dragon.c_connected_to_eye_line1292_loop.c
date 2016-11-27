#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int pos;
extern int  delta[8] ;
extern char  mx[20 * 20] ;

void loop()
{
#pragma scop

    // for(k = 0; k < 8; k++) 
    // 	if(board[pos + delta[k]] != 3) 
    // 		mx[pos + delta[k]] = 1;
	int cond[8];
	for(k = 0; k < 8; k++){ 
		int x =pos + delta[k];
		cond[k] = (int)(board[x] != 3);
	}
    for(k = 0; k < 8; k++){ 
    	int x =pos + delta[k];
    	mx[x] = 1*cond[k] + (1-cond[k])*mx[x];
	}

#pragma endscop
}
