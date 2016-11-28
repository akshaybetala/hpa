#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ii;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
struct intrusion_data
{
    int source_pos;
    int strength_pos;
    float strength;
    float attenuation;
};

struct influence_data
{
    char safe[(19 + 1) *(19 + 1)];
    float white_influence[(19 + 1) *(19 + 1)];
    float black_influence[(19 + 1) *(19 + 1)];
    float white_strength[(19 + 1) *(19 + 1)];
    float black_strength[(19 + 1) *(19 + 1)];
    float white_attenuation[(19 + 1) *(19 + 1)];
    float black_attenuation[(19 + 1) *(19 + 1)];
    float white_permeability[(19 + 1) *(19 + 1)];
    float black_permeability[(19 + 1) *(19 + 1)];
    int territory_segmentation[(19 + 1) *(19 + 1)];
    int moyo_segmentation[(19 + 1) *(19 + 1)];
    int area_segmentation[(19 + 1) *(19 + 1)];
    int region_type[3 * 19 * 19 + 1];
    int region_size[3 * 19 * 19 + 1];
    float region_territorial_value[3 * 19 * 19 + 1];
    int number_of_regions;
    int is_territorial_influence;
    float territory_value[(19 + 1) *(19 + 1)];
    int non_territory[(19 + 1) *(19 + 1)];
    int captured;
    int color_to_move;
    int queue[19 * 19];
    int intrusion_counter;
    struct intrusion_data intrusions[2 * 19 * 19];
};

extern struct influence_data* restrict q;
extern int  delta[8] ;

void loop()
{
#pragma scop
/*
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) if(board[ii] != 3 && q -> safe[ii])
        {
            int k;
            for(k = 0; k < 8; k++)
            {
                int d = delta[k];
                if(board[ii + d] != 3 && !q -> safe[ii + d])
                {
                    float reduction =(k < 4?0.25 : 0.65);
                    if(board[ii] == 2) q -> white_permeability[ii + d] *= reduction;
                    else q -> black_permeability[ii + d] *= reduction;
                }
            }
        }
*/

    for(ii = 21; ii <400; ii++) if(board[ii] != 3 && q -> safe[ii])
        {
            int k;
            for(k = 0; k < 8; k++)
            {
                int d = delta[k];
                if(board[ii + d] != 3 && !q -> safe[ii + d])
                {
                    float reduction =(k < 4?0.25 : 0.65);
                    if(board[ii] == 2) q -> white_permeability[ii + d] *= reduction;
                    else q -> black_permeability[ii + d] *= reduction;
                }
            }
        }






#pragma endscop
}
