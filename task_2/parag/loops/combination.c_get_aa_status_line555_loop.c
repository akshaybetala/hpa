#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int num_stones;
extern int  aa_status[(19 + 1) *(19 + 1)] ;
extern int  stones[19 * 19] ;

void loop()
{
#pragma scop

    for(k = 0; k < num_stones; k++) if(aa_status[stones[k]] != 3) return aa_status[stones[k]];

#pragma endscop
}
