#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int r;
extern int stackp;
extern char  active[20 * 20] ;
struct reading_cache
{
    int boardsize;
    char board[(19 + 1) *(19 + 1)];
    int movenum;
    int nodes;
    int score;
    int remaining_depth;
    int routine;
    int str;
    int result;
    int move;
    int stack[5];
    int move_color[5];
};

extern struct reading_cache* restrict entry;

void loop()
{
#pragma scop

    for(r = 0; r < stackp; r++) active[entry -> stack[r]] = 5;

#pragma endscop
}
