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
extern int  libs[2] ;

void loop()
{
#pragma scop

    for(k = 0; k < 2; k++) do
        {
            int u;
            for(u = 0; u < moves . num; u++) if(moves . pos[u] == libs[k])
                {
                    moves . score[u] += 0;
                    break;
                }
            if(u == moves . num && moves . num < 50)
            {
                moves . pos[moves . num] = libs[k];
                moves . score[moves . num] = 0;
                moves . num++;
            }
        }
        while(0);

#pragma endscop
}
