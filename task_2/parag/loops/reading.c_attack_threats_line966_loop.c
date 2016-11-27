#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int num_threats;
extern int max_points;
extern int* restrict codes;

void loop()
{
#pragma scop

    for(num_threats = 0; num_threats < max_points; num_threats++) if(codes[num_threats] == 0) break;

#pragma endscop
}
