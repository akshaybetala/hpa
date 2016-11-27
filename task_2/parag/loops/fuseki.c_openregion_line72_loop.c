#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int x;
extern int i1;
extern int i2;
extern int y;
extern int j1;
extern int j2;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;

void loop()
{
#pragma scop

    for(x = i1; x <= i2; x++) for(y = j1; y <= j2; y++) if(board[19 + 2 + x *(19 + 1) + y] != 0) return 0;

#pragma endscop
}
