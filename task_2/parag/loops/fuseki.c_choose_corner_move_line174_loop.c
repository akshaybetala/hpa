#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int sum_of_weights;
extern int * restrict table;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++) sum_of_weights += table[i];

#pragma endscop
}
