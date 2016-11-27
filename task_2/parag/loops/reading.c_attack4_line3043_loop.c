#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
struct reading_moves
{
    int pos[50];
    int score[50];
    int num;
};

extern struct reading_moves moves;

void loop()
{
#pragma scop

    for(k = 0; k < moves . num; k++) moves . score[k] += 5;

#pragma endscop
}
