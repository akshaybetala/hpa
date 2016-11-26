#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int  best_moves[10] ;
extern float  best_move_values[10] ;

void loop()
{
#pragma scop

    for(k = 0; k < 10; k++)
    {
        best_moves[k] = 0;
        best_move_values[k] = 0.0;
    }

#pragma endscop
}
