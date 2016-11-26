#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int  best_moves[10] ;
extern int move;
extern float  best_move_values[10] ;

void loop()
{
#pragma scop

    for(k = 0; k < 10; k++)
    {
        if(best_moves[k] == move)
        {
            int l;
            for(l = k; l < 9; l++)
            {
                best_moves[l] = best_moves[l + 1];
                best_move_values[l] = best_move_values[l + 1];
            }
            best_moves[9] = 0;
            best_move_values[9] = 0.0;
        }
    }

#pragma endscop
}
