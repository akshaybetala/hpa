int ii_ = 0;
unsigned char board_[(19 + 2) *(19 + 1) + 1];
char q_safe_[(19 + 1) *(19 + 1)];
int k_ = 0;
int delta_[8];
float q_territory_value_[(19 + 1) *(19 + 1)];
float q_black_permeability_[(19 + 1) *(19 + 1)];
float first_guess_[20 * 20];
float q_white_permeability_[(19 + 1) *(19 + 1)];
