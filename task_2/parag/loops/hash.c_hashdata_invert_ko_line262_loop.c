#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long Hashvalue;
typedef struct
{
    Hashvalue hashval[64 /(8 * sizeof(long ))];
} Hash_data;
extern Hash_data * restrict hd;
extern Hashvalue  ko_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] ;
extern int pos;

void loop()
{
#pragma scop

    for(i = 0; i < 64 /(8 * sizeof(long )); i++) hd -> hashval[i] ^= ko_hash[pos][i];

#pragma endscop
}
