#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern float val;
extern float  best_move_values[10] ;
extern int  best_moves[10] ;
extern int move;

void loop()
{
#pragma scop

    for(k = 9; k >= 0; k--) if(val > best_move_values[k])
        {
            if(k < 9)
            {
                best_move_values[k + 1] = best_move_values[k];
                best_moves[k + 1] = best_moves[k];
            }
            best_move_values[k] = val;
            best_moves[k] = move;
        }

#pragma endscop
}
