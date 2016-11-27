#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int liberties1;
extern int  ml[(19 + 1) *(19 + 1)] ;
extern int * restrict libs1;
extern int liberty_mark;

void loop()
{
#pragma scop

    for(k = 0; k < liberties1; k++) ml[libs1[k]] = liberty_mark;

#pragma endscop
}
