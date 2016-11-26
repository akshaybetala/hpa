#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int  gb[(19 + 1) *(19 + 1)] ;
extern int  bubbles[20 * 20] ;
extern int found_one;

void loop()
{
#pragma scop

    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++)
    {
        int white_neighbor = 0;
        int black_neighbor = 0;
        int new_color = 0;
        if(!(board[ii] != 3) || gb[ii] || bubbles[ii] == 3) continue;
        if(board[ii +(19 + 1)] != 3 && bubbles[ii +(19 + 1)] == 3 || board[ii - 1] != 3 && bubbles[ii - 1] == 3 || board[ii -(19 + 1)] != 3 && bubbles[ii -(19 + 1)] == 3 || board[ii + 1] != 3 && bubbles[ii + 1] == 3)
        {
            found_one = 1;
            bubbles[ii] = 3;
        }
        else
        {
            if(bubbles[ii] == 1 || board[ii +(19 + 1)] != 3 &&(gb[ii +(19 + 1)] > 0 || bubbles[ii +(19 + 1)] == 1) || board[ii - 1] != 3 &&(gb[ii - 1] > 0 || bubbles[ii - 1] == 1) || board[ii -(19 + 1)] != 3 &&(gb[ii -(19 + 1)] > 0 || bubbles[ii -(19 + 1)] == 1) || board[ii + 1] != 3 &&(gb[ii + 1] > 0 || bubbles[ii + 1] == 1)) white_neighbor = 1;
            if(bubbles[ii] == 2 || board[ii +(19 + 1)] != 3 &&(gb[ii +(19 + 1)] < 0 || bubbles[ii +(19 + 1)] == 2) || board[ii - 1] != 3 &&(gb[ii - 1] < 0 || bubbles[ii - 1] == 2) || board[ii -(19 + 1)] != 3 &&(gb[ii -(19 + 1)] < 0 || bubbles[ii -(19 + 1)] == 2) || board[ii + 1] != 3 &&(gb[ii + 1] < 0 || bubbles[ii + 1] == 2)) black_neighbor = 1;
            if(white_neighbor)
            {
                if(black_neighbor) new_color = 3;
                else new_color = 1;
            }
            else if(black_neighbor) new_color = 2;
            if(new_color && new_color != bubbles[ii])
            {
                found_one = 1;
                bubbles[ii] = new_color;
            }
        }
    }

#pragma endscop
}
