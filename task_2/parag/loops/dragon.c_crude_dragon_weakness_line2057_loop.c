#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern float  weakness_value[3] ;

void loop()
{
#pragma scop

    for(i = 0; i < 3; i++) for(j = i + 1; j < 3; j++) if(weakness_value[j] < weakness_value[i])
            {
                float tmp = weakness_value[i];
                weakness_value[i] = weakness_value[j];
                weakness_value[j] = tmp;
            }

#pragma endscop
}
