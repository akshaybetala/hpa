#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern char  active[20 * 20] ;
typedef unsigned char Intersection;
extern Intersection  shadow[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

    for(k = 19 + 2; k <(19 + 1) *(19 + 1); k++) active[k] = shadow[k];

#pragma endscop
}
