#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int m;
extern int n;
extern float  values[(19 + 1) *(19 + 1)] ;
extern float contribution;

void loop()
{
#pragma scop

    for(i = - 1; i <= 1; i++) for(j = - 1; j <= 1; j++) if(board[19 + 2 +(m + i) *(19 + 1) +(n + j)] == 0) values[19 + 2 +(m + i) *(19 + 1) +(n + j)] += contribution;

#pragma endscop
}
