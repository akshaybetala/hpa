#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int num_stones;
extern int value;
extern int  aa_values[(19 + 1) *(19 + 1)] ;
extern int  stones[19 * 19] ;

void loop()
{
#pragma scop

    // for(k = 0; k < num_stones; k++)
    // 	value += aa_values[stones[k]];
	int i = 0;
	for(k = num_stones - 1; k > 0; k--)
    	i += aa_values[stones[k]];
   	value +=i;
#pragma endscop
}
