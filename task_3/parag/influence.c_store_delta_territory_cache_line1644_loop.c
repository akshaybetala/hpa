#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern float  delta_territory_cache[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) delta_territory_cache[ii] =(- 2.0 * 19 * 19);

#pragma endscop
}
