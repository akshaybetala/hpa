#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int board_size;
extern int top_row;
extern int n;
extern char  mn[20 * 20] ;
extern int  left_corner[19] ;

void loop()
{
#pragma scop

    /*
    for(m = 0; m < board_size; m++)
    {
        if(top_row != - 1) break;
        for(n = 0; n < board_size; n++) if(mn[19 + 2 + m *(19 + 1) + n])
            {
                left_corner[0] = 19 + 2 + m *(19 + 1) + n;
                top_row = m;
                break;
            }
    }
    */

    //loop unswitching
    //removing break
    int fm = -1;
    int fn = -1;

    if(top_row != - 1){
        for(m = 0; m < board_size; m++)
        {
            for(n = 0; n < board_size; n++) {
                int cond = (int) ((mn[19 + 2 + m *(19 + 1) + n]) && (top_row < 0));
                top_row = m * cond + top_row * (1 - cond);
                fm = m * cond + fm * (1 - cond);
                fn = n * cond + fn * (1 - cond);
            }
        }
    }

    if(top_row >= 0) {
        m = fm;
        n = fn;
    }



#pragma endscop
}
