#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dfa_board_size;
extern int j;
extern int  dfa_p[21 * 4 * 21 * 4] ;
extern int  convert[3][4] ;
extern int color;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i < dfa_board_size; i++) for(j = 0; j < dfa_board_size; j++) dfa_p[4 * 21 * i + j +(4 * 21 * 21 + 21)] = convert[color][board[19 + 2 + i *(19 + 1) + j]];

#pragma endscop
}
