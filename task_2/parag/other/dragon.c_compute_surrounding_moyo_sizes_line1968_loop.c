#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
extern float  moyo_sizes[20 * 20] ;
extern float  moyo_values[20 * 20] ;

void loop()
{
#pragma scop

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        moyo_sizes[pos] = 0.0;
        moyo_values[pos] = 0.0;
    }

#pragma endscop
}
