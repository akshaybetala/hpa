#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int  active_caches[2] ;

void loop()
{
#pragma scop

    for(k = 0; k < 2; k++) active_caches[k] = 0;

#pragma endscop
}
