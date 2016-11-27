#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int q;
extern int * restrict table;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        q -= table[i];
        if(q < 0) break;
    }

#pragma endscop
}
