#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int board_size;
extern int bottom_row;
extern int n;
extern char  mn[20 * 20] ;

void loop()
{
#pragma scop

	/*
	for(m = board_size - 1; m >= 0; m--)
    {
        if(bottom_row != - 1) break;
        for(n = 0; n < board_size; n++) if(mn[19 + 2 + m *(19 + 1) + n])
            {
                bottom_row = m;
                break;
            }
    }
    */

    int fm = -1;
    int fn = -1;
	if(bottom_row != - 1) {
		for(m = board_size - 1; m >= 0; m--)
	    {
	        for(n = 0; n < board_size; n++) {
	        	int cond = (int) ((mn[19 + 2 + m *(19 + 1) + n]) && (bottom_row < 0));
                bottom_row = m * cond + bottom_row * (1 - cond);
                fm = m * cond + fm * (1 - cond);
                fn = n * cond + fn * (1 - cond);
	        }
	    }
	}

	if(bottom_row >= 0) {
        m = fm;
        n = fn;
    }
    

#pragma endscop
}
