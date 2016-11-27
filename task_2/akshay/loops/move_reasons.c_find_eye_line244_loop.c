#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int next_eye;
extern int  eyes[19 * 19 / 2] ;
extern int eye;
extern int  eyecolor[19 * 19 / 2] ;
extern int color;

void loop()
{
#pragma scop
	
	//for(k = 0; k < next_eye; k++) if(eyes[k] == eye && eyecolor[k] == color) return k;

	int cond[next_eye];
    for(k = 0; k < next_eye; k++) cond[k] = (eyes[k] == eye && eyecolor[k] == color);
	for(k = 0; k < next_eye; k++) if(cond[k]) return k;

#pragma endscop
}
