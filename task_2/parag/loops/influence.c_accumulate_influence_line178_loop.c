#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern int  working[20 * 20] ;

void loop()
{
#pragma scop

    for(ii = 0; ii <(19 + 1) *(19 + 1); ii++) working[ii] = 0;

#pragma endscop
}
