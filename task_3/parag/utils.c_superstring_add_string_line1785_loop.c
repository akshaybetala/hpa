#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int num_my_libs;
extern char  ml[(19 + 1) *(19 + 1)] ;
extern int  my_libs[724 / 3] ;
extern int do_add;
extern int liberty_cap;
extern int * restrict libs;
extern int * restrict num_libs;
extern int maxlibs;

void loop()
{
#pragma scop

    for(k = 0; k < num_my_libs; k++)
    {
        if(ml[my_libs[k]]) continue;
        ml[my_libs[k]] = 1;
        if(do_add &&(liberty_cap == 0 || num_my_libs <= liberty_cap))
        {
            libs[ *num_libs] = my_libs[k];
            ( *num_libs)++;
            if( *num_libs == maxlibs) break;
        }
    }

#pragma endscop
}
