#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern char  goal[(19 + 1) *(19 + 1)] ;
extern int  queue[19 * 19] ;
extern int queue_end;
extern int  mx[20 * 20] ;

void loop()
{
#pragma scop

    // for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) 
    // 	if(board[ii] != 3 && goal[ii]) 
    // 		(queue[queue_end++] = ii , mx[ii] = 1);

	int cond[400];
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) 
    	cond[ii] = (board[ii] != 3 && goal[ii]);

    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++){ 
    	if(!cond[ii]) continue;
    	(queue[queue_end++] = ii , mx[ii] = 1);
    }

    // int cond;
    // for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) 
    // {
    //     cond = (board[ii] != 3 && goal[ii]);
    //     mx[ii] = cond + (1-cond)*mx[ii];
    //     queue_end+=cond;
    //     queue[queue_end] = ii*cond + (1-cond)*queue[queue_end];        
    // }


#pragma endscop
}
