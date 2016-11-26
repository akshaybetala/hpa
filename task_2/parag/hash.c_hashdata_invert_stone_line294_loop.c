#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned long Hashvalue;
typedef struct
{
    Hashvalue hashval[64 /(8 * sizeof(long ))];
} Hash_data;
extern Hash_data * restrict hd;
extern Hashvalue  white_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] ;
extern int pos;

void loop()
{
#pragma scop

    for(k = 0; k < 64 /(8 * sizeof(long )); k++) hd -> hashval[k] ^= white_hash[pos][k];

#pragma endscop
}
