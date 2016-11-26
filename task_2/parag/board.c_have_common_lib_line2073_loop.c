#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int liberties1;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int * restrict libs1;
extern int str2;
extern int  string_number[(19 + 1) *(19 + 1)] ;
extern int * restrict lib;

void loop()
{
#pragma scop

    for(k = 0; k < liberties1; k++)
    {
        if(board[libs1[k] +(19 + 1)] == board[str2] && string_number[libs1[k] +(19 + 1)] == string_number[str2] || board[libs1[k] - 1] == board[str2] && string_number[libs1[k] - 1] == string_number[str2] || board[libs1[k] -(19 + 1)] == board[str2] && string_number[libs1[k] -(19 + 1)] == string_number[str2] || board[libs1[k] + 1] == board[str2] && string_number[libs1[k] + 1] == string_number[str2])
        {
            if(lib) *lib = libs1[k];
            return 1;
        }
    }

#pragma endscop
}
