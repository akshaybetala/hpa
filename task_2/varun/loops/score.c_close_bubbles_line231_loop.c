#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  gb[(19 + 1) *(19 + 1)] ;
extern int  bubbles[20 * 20] ;

void loop()
{
#pragma scop

    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++)
    {
        if(!(board[ii] != 3) || gb[ii]) continue;
        if(bubbles[ii] == 1) gb[ii] = 1;
        if(bubbles[ii] == 2) gb[ii] = - 1;
    }

#pragma endscop
}
