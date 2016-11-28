#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int board_size;
extern char  mn[20 * 20] ;
extern int top_row;
extern int  right_corner[19] ;

void loop()
{
#pragma scop

	/*
    for(n = board_size - 1; n >= 0; n--) {
    	if(mn[19 + 2 + top_row *(19 + 1) + n])
        {
            right_corner[0] = 19 + 2 + top_row *(19 + 1) + n;
            break;
        }
    }
    */
    

    //invariant code    
    int t = 19 + 2 + top_row *(19 + 1);
    int fn = -2;
    for(n = board_size - 1; n >= 0; n--) {
        int cond = (int) (( (mn[t + n])) && (fn == -2));
        fn = n * cond + -2 * (1 - cond);
    	
    }

    if(fn != -2) {
        n = fn;
        right_corner[0] = t + n;
    }
    
    	



#pragma endscop
}
