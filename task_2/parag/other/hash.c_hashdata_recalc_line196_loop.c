#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern Intersection * restrict p;
extern int i;
typedef unsigned long Hashvalue;
typedef struct
{
    Hashvalue hashval[64 /(8 * sizeof(long ))];
} Hash_data;
extern Hash_data * restrict target;
extern Hashvalue  white_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] ;
extern Hashvalue  black_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] ;

void loop()
{
#pragma scop
//VECTORIZED
    int x = 64 /(8 * sizeof(long ));
 for(pos = 21; pos <400; pos++)
    {   
        int temp = p[pos];
        if(board[pos] == 3 && temp!=1 && temp!=2) continue;
        for(i = 0; i < x; i++) 
            target -> hashval[i] ^= (2-temp)*white_hash[pos][i] + (temp-1)*black_hash[pos][i];
    }

    // for(pos = 19 + 2; pos <(19 + 1) *(19 + 1); pos++)
    // {
    //     if(!(board[pos] != 3)) continue;
    //     switch(p[pos])
    //     {
    //     default:
    //         {}
    //     case 0:
    //         break;
    //     case 1:
    //     {
    //         for(i = 0; i < 64 /(8 * sizeof(long )); i++) target -> hashval[i] ^= white_hash[pos][i];
    //         break;
    //     }
    //     case 2:
    //     {
    //         for(i = 0; i < 64 /(8 * sizeof(long )); i++) target -> hashval[i] ^= black_hash[pos][i];
    //         break;
    //     }
    //     }
    // }

#pragma endscop
}
