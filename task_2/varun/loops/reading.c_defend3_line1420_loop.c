#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int liberties;
struct reading_moves
{
    int pos[50];
    int score[50];
    int num;
};

extern struct reading_moves moves;
extern int  libs[3] ;

void loop()
{
#pragma scop

    for(k = 0; k < liberties; k++)
    {
        moves . pos[k] = libs[k];
        moves . score[k] = 0;
    }

#pragma endscop
}
