#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
extern int  dfa_p[21 * 4 * 21 * 4] ;

void loop()
{
#pragma scop

    for(ii = 0; ii < 4 * 21 * 4 * 21; ii++) dfa_p[ii] = 3;

#pragma endscop
}
