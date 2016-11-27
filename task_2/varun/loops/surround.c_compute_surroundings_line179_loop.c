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

    for(n = board_size - 1; n >= 0; n--) if(mn[19 + 2 + top_row *(19 + 1) + n])
        {
            right_corner[0] = 19 + 2 + top_row *(19 + 1) + n;
            break;
        }

#pragma endscop
}
