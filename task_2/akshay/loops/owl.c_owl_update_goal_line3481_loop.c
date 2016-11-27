#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int num_stones;
struct eyevalue
{
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};

struct eye_data
{
    int color;
    int esize;
    int msize;
    int origin;
    struct eyevalue value;
    int attack_point;
    int defense_point;
    char marginal;
    char type;
    char neighbors;
    char marginal_neighbors;
    char cut;
};

struct half_eye_data
{
    float value;
    char type;
    int num_attacks;
    int attack_point[4];
    int num_defends;
    int defense_point[4];
};

struct local_owl_data
{
    char goal[(19 + 1) *(19 + 1)];
    char boundary[(19 + 1) *(19 + 1)];
    char escape_values[(19 + 1) *(19 + 1)];
    int color;
    struct eye_data my_eye[(19 + 1) *(19 + 1)];
    struct half_eye_data half_eye[(19 + 1) *(19 + 1)];
    int lunch[10];
    int lunch_attack_code[10];
    int lunch_attack_point[10];
    int lunch_defend_code[10];
    int lunch_defense_point[10];
    char inessential[(19 + 1) *(19 + 1)];
    int lunches_are_current;
    char safe_move_cache[(19 + 1) *(19 + 1)];
    int restore_from;
    int number_in_stack;
};

extern struct local_owl_data* restrict owl;
extern int  stones[19 * 19] ;
extern int do_add;

void loop()
{
#pragma scop
/*
    for(k = 0; k < num_stones; k++) if(owl -> goal[stones[k]] != 0)
        {
            do_add = 1;
            break;
        }
*/
    int temp[num_stones];
    for(k = 0; k < num_stones; k++) temp[k] = (owl -> goal[stones[k]] != 0);
        
    for(k = 0; k < num_stones; k++) if(temp[k])
        {
            do_add = 1;
            break;
        }


#pragma endscop
}
