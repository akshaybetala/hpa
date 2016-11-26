#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned char Intersection;
extern Intersection  board[(19 + 2) *(19 + 1) + 1] ;
extern int pos;
extern int  delta[8] ;
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

extern struct local_owl_data* restrict current_owl_data;

void loop()
{
#pragma scop

    for(k = 0; k < 8; k++) if(board[pos + delta[k]] != 3 && current_owl_data -> goal[pos + delta[k]]) return - 10;

#pragma endscop
}
