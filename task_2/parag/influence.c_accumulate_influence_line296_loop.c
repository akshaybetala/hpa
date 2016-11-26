#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int queue_end;
extern int ii;
extern int  queue[20 * 20] ;
extern int  working[20 * 20] ;
extern int  influence[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(k = 0; k < queue_end; k++)
    {
        ii = queue[k];
        if(working[ii] >((int )(0.02 *(1 << 12))) + 0.5 || influence[ii] == 0) influence[ii] += working[ii];
        working[ii] = 0;
    }

#pragma endscop
}
