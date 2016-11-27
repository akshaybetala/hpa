#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int r;
extern int num_moves;
extern int  distances[362] ;

void loop()
{
#pragma scop

    /*
    for(r = 0; r < num_moves; r++) if(distances[r] > distances[0] + 1500) break;
	*/

    //loop invariant code outside

    int t = distances[0] + 1500;
	for(r = 0; r < num_moves; r++) if(distances[r] > t) break;

#pragma endscop
}
