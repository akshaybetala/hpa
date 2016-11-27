#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int board_size;
extern int n;
extern float  values[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(m = 0; m < board_size; m++) for(n = 0; n < board_size; n++) values[19 + 2 + m *(19 + 1) + n] = 0.0;

#pragma endscop
}
