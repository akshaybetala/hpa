#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int l;
extern int  statistics[6 + 1][20] ;

void loop()
{
#pragma scop

	int * s = (int *)(& statistics);
    for(k = 0; k < 140; ++k) 
			s[k] = 0;
    // for(k = 0; k < 6 + 1; ++k) 
    // 	for(l = 0; l < 20; ++l) 
    // 		statistics[k][l] = 0;

#pragma endscop
}
