#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int  left_corner[19] ;
extern int left_corners;
extern int  right_corner[19] ;
extern int right_corners;
extern char  mn[20 * 20] ;
extern int bottom_row;

void loop()
{
#pragma scop

    for(n = left_corner[left_corners - 1] %(19 + 1) - 1; n <= right_corner[right_corners - 1] %(19 + 1) - 1; n++) mn[19 + 2 + bottom_row *(19 + 1) + n] = 1;

#pragma endscop
}
