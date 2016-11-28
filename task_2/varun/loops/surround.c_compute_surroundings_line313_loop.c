#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int dpos;
extern int surrounded;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  mf[20 * 20] ;
extern int color;
extern char  mn[20 * 20] ;
extern int other;

void loop()
{
#pragma scop

    /*
    for(dpos = 19 + 2; dpos <(19 + 1) *(19 + 1) && surrounded; dpos++) {
       if(board[dpos] != 3 && mf[dpos])
        {
            if(board[dpos -(19 + 1)] != 3 && board[dpos -(19 + 1)] == 0 && board[dpos -(19 + 1) -(19 + 1)] != 3 && board[dpos -(19 + 1) -(19 + 1)] == color && mn[dpos -(19 + 1) -(19 + 1)] != 1 && board[dpos -(19 + 1) + 1] != 3 && board[dpos -(19 + 1) + 1] != other && board[dpos -(19 + 1) - 1] != 3 && board[dpos -(19 + 1) - 1] != other || board[dpos +(19 + 1)] != 3 && board[dpos +(19 + 1)] == 0 && board[dpos +(19 + 1) +(19 + 1)] != 3 && board[dpos +(19 + 1) +(19 + 1)] == color && mn[dpos +(19 + 1) +(19 + 1)] != 1 && board[dpos +(19 + 1) + 1] != 3 && board[dpos +(19 + 1) + 1] != other && board[dpos +(19 + 1) - 1] != 3 && board[dpos +(19 + 1) - 1] != other || board[dpos + 1] != 3 && board[dpos + 1] == 0 && board[dpos + 1 + 1] != 3 && board[dpos + 1 + 1] == color && mn[dpos + 1 + 1] != 1 && board[dpos + 1 -(19 + 1)] != 3 && board[dpos + 1 -(19 + 1)] != other && board[dpos + 1 +(19 + 1)] != 3 && board[dpos + 1 +(19 + 1)] != other || board[dpos - 1] != 3 && board[dpos - 1] == 0 && board[dpos - 1 - 1] != 3 && board[dpos - 1 - 1] == color && mn[dpos - 1 - 1] != 1 && board[dpos - 1 -(19 + 1)] != 3 && board[dpos - 1 -(19 + 1)] != other && board[dpos - 1 +(19 + 1)] != 3 && board[dpos - 1 +(19 + 1)] != other) 
            {
            	surrounded = 0;
            }
        }
    }
    */

    int fpos = 0;
    for(dpos = 19 + 2; dpos <(19 + 1) *(19 + 1); dpos++) {
       int cond = (int) (( (board[dpos] != 3 && mf[dpos]) && (board[dpos -(19 + 1)] != 3 && board[dpos -(19 + 1)] == 0 && board[dpos -(19 + 1) -(19 + 1)] != 3 && board[dpos -(19 + 1) -(19 + 1)] == color && mn[dpos -(19 + 1) -(19 + 1)] != 1 && board[dpos -(19 + 1) + 1] != 3 && board[dpos -(19 + 1) + 1] != other && board[dpos -(19 + 1) - 1] != 3 && board[dpos -(19 + 1) - 1] != other || board[dpos +(19 + 1)] != 3 && board[dpos +(19 + 1)] == 0 && board[dpos +(19 + 1) +(19 + 1)] != 3 && board[dpos +(19 + 1) +(19 + 1)] == color && mn[dpos +(19 + 1) +(19 + 1)] != 1 && board[dpos +(19 + 1) + 1] != 3 && board[dpos +(19 + 1) + 1] != other && board[dpos +(19 + 1) - 1] != 3 && board[dpos +(19 + 1) - 1] != other || board[dpos + 1] != 3 && board[dpos + 1] == 0 && board[dpos + 1 + 1] != 3 && board[dpos + 1 + 1] == color && mn[dpos + 1 + 1] != 1 && board[dpos + 1 -(19 + 1)] != 3 && board[dpos + 1 -(19 + 1)] != other && board[dpos + 1 +(19 + 1)] != 3 && board[dpos + 1 +(19 + 1)] != other || board[dpos - 1] != 3 && board[dpos - 1] == 0 && board[dpos - 1 - 1] != 3 && board[dpos - 1 - 1] == color && mn[dpos - 1 - 1] != 1 && board[dpos - 1 -(19 + 1)] != 3 && board[dpos - 1 -(19 + 1)] != other && board[dpos - 1 +(19 + 1)] != 3 && board[dpos - 1 +(19 + 1)] != other)));
       int cond2 = (int) (fpos == 0 && cond >0);
       fpos += dpos*cond2 ;
    }
    if (fpos != 0) {
        dpos = fpos;
        surrounded = 0;
    }
    	

#pragma endscop
}
