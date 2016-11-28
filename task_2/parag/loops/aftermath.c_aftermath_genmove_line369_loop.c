#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int move;
extern int  delta[8] ;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  distance[20 * 20] ;

void loop()
{
#pragma scop
    
    int d = distance[move] - 1;
    for(k = 0; k < 4; k++)
    {
        int pos2 = move + delta[k];
        if(board[pos2] == 0 && distance[pos2] == d)
        {
            move = pos2;
            break;
        }
    }
    

    // for(k = 0; k < 4; k++)
    // {
    //     int pos2 = move + delta[k];
    //     if(board[pos2] != 3 && board[pos2] == 0 && distance[pos2] == distance[move] - 1)
    //     {
    //         move = pos2;
    //         break;
    //     }
    // }

#pragma endscop
}
