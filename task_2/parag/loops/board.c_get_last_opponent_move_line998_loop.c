#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int move_history_pointer;
extern int  move_history_color[500] ;
extern int color;
extern int  move_history_pos[500] ;

void loop()
{
#pragma scop

    for(k = move_history_pointer - 1; k >= 0; k--) if(move_history_color[k] == 1 + 2 - color) return move_history_pos[k];

#pragma endscop
}
