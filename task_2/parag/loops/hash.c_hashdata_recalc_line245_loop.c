#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long Hashvalue;
typedef struct
{
    Hashvalue hashval[64 /(8 * sizeof(long ))];
} Hash_data;
extern Hash_data * restrict target;
extern Hashvalue  ko_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] ;
extern int ko_pos;

void loop()
{
#pragma scop

    for(i = 0; i < 64 /(8 * sizeof(long )); i++) target -> hashval[i] ^= ko_hash[ko_pos][i];

#pragma endscop
}
