#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int  left_corner[19] ;
extern int  right_corner[19] ;
extern char  mn[20 * 20] ;
extern int top_row;

void loop()
{
#pragma scop

    for(n = left_corner[0] %(19 + 1) - 1; n <= right_corner[0] %(19 + 1) - 1; n++) mn[19 + 2 + top_row *(19 + 1) + n] = 1;

#pragma endscop
}
