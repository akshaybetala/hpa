#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern float  weakness_value[3] ;

void loop()
{
#pragma scop

	float duplicate[3];
	for(int p = 0; p<3; p++){
		duplicate[p] = weakness_value[p];
	}

    for(i = 0; i < 3; i++){
	 for(j = i + 1; j < 3; j++)
		if( duplicate[j] < weakness_value[i])
            {
                	float tmp = weakness_value[i];
                	weakness_value[i] = duplicate[j];
                	weakness_value[j] = tmp;
                	duplicate[j] = tmp;
           	}
    }   		

#pragma endscop
}
