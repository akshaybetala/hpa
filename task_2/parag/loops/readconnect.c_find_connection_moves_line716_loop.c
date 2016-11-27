#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int num_moves;
extern int  distances[362] ;
extern int j;
extern int  moves[362] ;

void loop()
{
#pragma scop

    for(i = 0; i < num_moves; i++)
    {
        int mindistance = distances[i];
        int min_at = i;
        for(j = i + 1; j < num_moves; j++)
        {
            if(distances[j] < mindistance)
            {
                mindistance = distances[j];
                min_at = j;
            }
        }
        if(min_at != i)
        {
            int temp = moves[i];
            int tempmin = distances[i];
            moves[i] = moves[min_at];
            distances[i] = distances[min_at];
            moves[min_at] = temp;
            distances[min_at] = tempmin;
        }
    }

#pragma endscop
}
