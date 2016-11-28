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
    //merge condition
    int t = distances[0] + 1500;
	int fr = -1;
	for(r = 0; r < num_moves ; r++) {
		int cond = (int) ((distances[r] > t) && fr < 0);
		fr = r * cond + fr * (1 - cond);
	}

	if(fr > 0)
		r = fr;

#pragma endscop
}
