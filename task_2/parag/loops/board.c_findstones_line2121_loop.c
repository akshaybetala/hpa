#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int maxstones;
extern int size;
extern int * restrict stones;
extern int pos;
extern int  next_stone[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop
	// int n;
	// if(maxstones < size)
	// 	n = maxstones;
	// else
	// 	n = size;
	stones[0] = pos;
	for(k = 1; k < maxstones && k < size; k++)
	{	
		stones[k] = next_stone[stones[k-1]];
        // stones[k] = pos;
        // pos = next_stone[pos];
    }
		
    // for(k = 0; k < maxstones && k < size; k++)
	// {
 //        stones[k] = pos;
 //        pos = next_stone[pos];
 //    }
	

#pragma endscop
}
