#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int dpos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  mn[20 * 20] ;
extern int k;
extern int  delta[8] ;

void loop()
{
#pragma scop

	/*
	for(dpos = 19 + 2; dpos <(19 + 1) *(19 + 1); dpos++) {
    	if(board[dpos] != 3 && mn[dpos] == 1) {
    		for(k = 0; k < 4; k++) {
    			if(board[dpos + delta[k]] != 3 && !mn[dpos + delta[k]]) mn[dpos + delta[k]] = 2;
    		}
    	}
    }
    */

	// int start = 21;
	// int end = (19 + 1) *(19 + 1);
	// for(dpos = start; dpos < end; dpos++) {
 //    	if(board[dpos] != 3 && mn[dpos] == 1) {
 //    		for(k = 0; k < 4; k++) {
 //    			if(board[dpos + delta[k]] != 3 && !mn[dpos + delta[k]]) mn[dpos + delta[k]] = 2;
 //    		}
 //    	}
 //    }

    // int start = 21;
    // int end = (19 + 1) *(19 + 1);

    // int x[421], y[421];
    // for(dpos = 0; dpos < 421; dpos++) {
    //     x[dpos]= (int) (board[dpos] != 3 && mn[dpos] == 1);
    //     y[dpos]= (int) (board[dpos] != 3 && !mn[dpos]);
    // }


    // for(dpos = start; dpos < end; dpos++) {
    //     for(k = 0; k < 4; k++) {
    //         int temp = (int) (x[dpos] && y[dpos + delta[k]]);
    //         mn[dpos + delta[k]] = mn[dpos + delta[k]] * (1-temp) + 2*temp;
            
    //     }
    // }

    for(dpos = 19 + 2; dpos <(19 + 1) *(19 + 1); dpos++) {
        
            for(k = 0; k < 4; k++) {
                int temp = (int) ((board[dpos] != 3 && mn[dpos] == 1) && (board[dpos + delta[k]] != 3 && !mn[dpos + delta[k]]));
                mn[dpos + delta[k]] = mn[dpos + delta[k]] * (1-temp) + 2*temp;
            }
        
    }
    

#pragma endscop
}
