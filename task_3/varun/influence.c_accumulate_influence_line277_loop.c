#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int d;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int ii;
extern int  delta[8] ;
extern char  safe[(19 + 1) *(19 + 1)] ;
extern int  deltai[8] ;
extern int delta_i;
extern int  deltaj[8] ;
extern int delta_j;
extern int queue_start;
extern int  permeability_array[(19 + 1) *(19 + 1)] ;
extern int current_strength;
extern int b;
extern int  working[20 * 20] ;
extern int  queue[20 * 20] ;
extern int queue_end;

void loop()
{
#pragma scop

    for(d = 0; d < 4; d++) if(board[ii + delta[d]] != 3) do
            {
                if(!safe[ii + delta[d]] &&(deltai[d] * delta_i + deltaj[d] * delta_j > 0 || queue_start == 1))
                {
                    int contribution;
                    int permeability = permeability_array[ii];
                    if(0)
                    {
                        permeability = permeability *((permeability_array[ii +(deltai[d] *(19 + 1) + 0)] < permeability_array[ii +(0 *(19 + 1) + deltaj[d])]?permeability_array[ii +(0 *(19 + 1) + deltaj[d])] : permeability_array[ii +(deltai[d] *(19 + 1) + 0)])) /(1 << 12);
                        if(permeability == 0) continue;
                    }
                    contribution = current_strength * permeability /(1 << 12);
                    if(queue_start != 1)
                    {
                        int a = deltai[d] * delta_i + deltaj[d] * delta_j;
                        contribution *= a * a;
                        contribution = b * contribution /(1 << 12);
                    }
                    if(contribution <=((int )(0.02 *(1 << 12))) + 0.5) continue;
                    if(working[ii + delta[d]] == 0)
                    {
                        queue[queue_end] = ii + delta[d];
                        queue_end++;
                    }
                    working[ii + delta[d]] += contribution;
                }
            }
            while(0);

#pragma endscop
}
