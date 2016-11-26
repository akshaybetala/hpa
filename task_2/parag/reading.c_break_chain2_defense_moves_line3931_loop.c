#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int saved_num_moves;
struct reading_moves
{
    int pos[50];
    int score[50];
    int num;
};

extern struct reading_moves* restrict moves;

void loop()
{
#pragma scop

    for(k = saved_num_moves; k < moves -> num; k++) moves -> score[k] = - 2;

#pragma endscop
}
