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
extern int k;
extern int  delta[8] ;
extern float  first_guess[20 * 20] ;

void loop()
{
#pragma scop
/*
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) if(board[ii] != 3)
        {
            if(!q -> safe[ii])
            {
                for(k = 0; k < 4; k++)
                {
                    if(!(board[ii + delta[k]] != 3)) continue;
                    if(q -> territory_value[ii] > 0.0)
                    {
                        if(!q -> safe[ii + delta[k]])
                        {
                            float neighbor_val =((q -> black_permeability[ii + delta[k]] * first_guess[ii + delta[k]]) +(1.0 - q -> black_permeability[ii + delta[k]]) * first_guess[ii]);
                            q -> territory_value[ii] =(0 <((q -> territory_value[ii] < neighbor_val?q -> territory_value[ii] : neighbor_val))?((q -> territory_value[ii] < neighbor_val?q -> territory_value[ii] : neighbor_val)) : 0);
                        }
                    }
                    else
                    {
                        if(!q -> safe[ii + delta[k]])
                        {
                            float neighbor_val = q -> white_permeability[ii + delta[k]] * first_guess[ii + delta[k]] +(1 - q -> white_permeability[ii + delta[k]]) * first_guess[ii];
                            q -> territory_value[ii] =(0 <((q -> territory_value[ii] < neighbor_val?neighbor_val : q -> territory_value[ii]))?0 :((q -> territory_value[ii] < neighbor_val?neighbor_val : q -> territory_value[ii])));
                        }
                    }
                }
            }
        }

*/
    int cond[400];

    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++) cond[ii] = (!q -> safe[ii] && board[ii] != 3);
            
    for(ii = 19 + 2; ii <(19 + 1) *(19 + 1); ii++){
        if(cond[ii])
        {
            if(q -> territory_value[ii] > 0.0)
            {
                for(k = 0; k < 4; k++)
                {
                    if(board[ii + delta[k]] == 3 || q -> safe[ii + delta[k]] ) continue;
                    float neighbor_val =((q -> black_permeability[ii + delta[k]] * first_guess[ii + delta[k]]) +(1.0 - q -> black_permeability[ii + delta[k]]) * first_guess[ii]);
                    q -> territory_value[ii] =(0 <((q -> territory_value[ii] < neighbor_val?q -> territory_value[ii] : neighbor_val))?((q -> territory_value[ii] < neighbor_val?q -> territory_value[ii] : neighbor_val)) : 0);
                    
                }
            }
            else
            {
                for(k = 0; k < 4; k++)
                {
                    if(board[ii + delta[k]] == 3 || q -> safe[ii + delta[k]]) continue;
                    float neighbor_val = q -> white_permeability[ii + delta[k]] * first_guess[ii + delta[k]] +(1 - q -> white_permeability[ii + delta[k]]) * first_guess[ii];
                    q -> territory_value[ii] =(0 <((q -> territory_value[ii] < neighbor_val?neighbor_val : q -> territory_value[ii]))?0 :((q -> territory_value[ii] < neighbor_val?neighbor_val : q -> territory_value[ii])));
                    
                    
                }
            }            
        }
    }

#pragma endscop
}
