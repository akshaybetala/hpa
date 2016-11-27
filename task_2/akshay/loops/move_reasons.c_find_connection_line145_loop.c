#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int next_connection;
extern int  conn_worm1[4 * 2 * 19 * 19 / 3] ;
extern int worm1;
extern int  conn_worm2[4 * 2 * 19 * 19 / 3] ;
extern int worm2;

void loop()
{
#pragma scop

    // for(k = 0; k < next_connection; k++) if(conn_worm1[k] == worm1 && conn_worm2[k] == worm2) return k;

	int cond[next_connection];
    for(k = 0; k < next_connection; k++) cond[k] = (conn_worm1[k] == worm1 && conn_worm2[k] == worm2);
	for(k = 0; k < next_connection; k++) if(cond[k]) return k;



#pragma endscop
}
