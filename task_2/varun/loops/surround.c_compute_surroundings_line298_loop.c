#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int board_size;
extern int n;
extern char  mf[20 * 20] ;
extern char  mn[20 * 20] ;
extern int surrounded;

void loop()
{
#pragma scop

    for(m = 0; m < board_size; m++) for(n = 0; n < board_size; n++)
        {
            if(mf[19 + 2 + m *(19 + 1) + n])
            {
                if(mn[19 + 2 + m *(19 + 1) + n] == 0)
                {
                    surrounded = 0;
                    break;
                }
                else if(mn[19 + 2 + m *(19 + 1) + n] == 2) surrounded = 2;
            }
        }

#pragma endscop
}
