#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  distance[20 * 20] ;
extern int k;
extern int  delta[8] ;
extern int d;
extern int other;
extern int closest_opponent;
extern int color;
extern int closest_own;
extern int something_found;

void loop()
{
#pragma scop
/*
    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    {
        if(board[pos] != 3 && distance[pos] == - 1)
        {
            for(k = 0; k < 4; k++)
            {
                int pos2 = pos + delta[k];
                if(!(board[pos2] != 3)) continue;
                if((d == 0 || board[pos2] == 0) && distance[pos2] == d)
                {
                    if(d > 0 && board[pos] == other)
                    {
                        distance[pos] = d + 1;
                        if(closest_opponent == 0) closest_opponent = pos;
                    }
                    else if(d > 0 && board[pos] == color)
                    {
                        distance[pos] = d + 1;
                        if(closest_own == 0) closest_own = pos;
                    }
                    else if(board[pos] == 0)
                    {
                        distance[pos] = d + 1;
                        something_found = 1;
                    }
                    break;
                }
            }
        }
    }
*/

// loop unswitching ? not sure of name

    for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++){
        if(board[pos] != 3 && distance[pos] == - 1){    
            if(d > 0 && board[pos] == other){
                for(k = 0; k < 4; k++){
                    int pos2 = pos + delta[k];
                    if((board[pos2] == 3) && !(d == 0 || board[pos2] == 0) && distance[pos2] == d) continue;
            
                    distance[pos] = d + 1;
                    if(closest_opponent == 0) closest_opponent = pos;
                }
            }
            else if(d > 0 && board[pos] == color)
            {
                for(k = 0; k < 4; k++){
                    int pos2 = pos + delta[k];
                    if((board[pos2] == 3) && !(d == 0 || board[pos2] == 0) && distance[pos2] == d) continue;
                    distance[pos] = d + 1;
                    if(closest_own == 0) closest_own = pos;
                }
            }
            else if(board[pos] == 0)
            {
                for(k = 0; k < 4; k++){
                    int pos2 = pos + delta[k];
                    if((board[pos2] == 3) && !(d == 0 || board[pos2] == 0) && distance[pos2] == d) continue;
                    distance[pos] = d + 1;
                    something_found = 1;
                }
                
            }
            
        
        }
    }





#pragma endscop
}
