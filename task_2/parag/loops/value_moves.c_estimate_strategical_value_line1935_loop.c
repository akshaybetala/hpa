#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int aa;
extern float  dragon_value[20 * 20] ;

void loop()
{
#pragma scop

    for(aa = 19 + 2; aa <(19 + 1) *(19 + 1); aa++) dragon_value[aa] = 0.0;

#pragma endscop
}
