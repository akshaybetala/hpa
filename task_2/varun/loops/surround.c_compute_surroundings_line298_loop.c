#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int board_size;
extern int n;
extern char  mf[20 * 20] ;
extern char  mn[20 * 20] ;
extern int surrounded;

void loop()
{
#pragma scop


    int cond[19+2+board_size*(19+1)+ board_size];
    for(m = 0; m < board_size; m++) {
        for(n = 0; n < board_size; n++)
        {
            int x = 19 + 2 + m *(19 + 1) + n ;
            cond[x] = (int)(mf[x]!=0)*((int)(mn[x]==0) + 2*(int)(mn[x]==2) + 1);
        }
    }
    
    for(m = 0; m < board_size; m++) {
        for(n = 0; n < board_size; n++)
        {
            int x = 19 + 2 + m *(19 + 1) + n ;
            if(cond[x]==2){
                surrounded = 0;
                break;
            }
            if(cond[x]==3)surrounded = 2;     
        }
    }

        

#pragma endscop
}
