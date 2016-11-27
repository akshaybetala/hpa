#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  nworms[20 * 20] ;
extern int * restrict ncw;
extern int k;
extern int (* restrict cw)[4];
extern int  worms[20 * 20][2 * 18] ;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(!(board[pos] != 3)) continue;
        if(nworms[pos] > 4) ncw[pos] = 0;
        else ncw[pos] = nworms[pos];
        for(k = 0; k < ncw[pos]; k++) cw[pos][k] = worms[pos][k];
    }

#pragma endscop
}
