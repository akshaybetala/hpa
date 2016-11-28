#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
extern float  values[(19 + 1) *(19 + 1)] ;

void loop()
{
#pragma scop

//    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++) values[pos] = 0.0;
	for(pos = (19 + 1) *(19 + 1)-1; pos > 20; pos--) values[pos] = 0.0;

#pragma endscop
}
