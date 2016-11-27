#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int board_size;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;

void loop()
{
#pragma scop

    for(k = 0; k <(19 + 2) *(19 + 1) + 1; k++) if(!(((unsigned int )(k /(19 + 1) - 1)) <((unsigned int )board_size) &&((unsigned int )(k %(19 + 1) - 1)) <((unsigned int )board_size))) if(board[k] != 3) return k;

#pragma endscop
}
