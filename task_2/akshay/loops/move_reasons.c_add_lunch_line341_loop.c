#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int next_lunch;
extern int  lunch_dragon[2 * 19 * 19 / 3] ;
extern int dragon1;
extern int  lunch_worm[2 * 19 * 19 / 3] ;
extern int worm1;

void loop()
{
#pragma scop
/*
    for(k = 0; k < next_lunch; k++) if(lunch_dragon[k] == dragon1 && lunch_worm[k] == worm1) return ;
*/
	
	int cond[next_lunch];
    for(k = 0; k < next_lunch; k++) cond[k] = (lunch_dragon[k] == dragon1 && lunch_worm[k] == worm1);
	for(k = 0; k < next_lunch; k++) if(cond[k]) return;


#pragma endscop
}
