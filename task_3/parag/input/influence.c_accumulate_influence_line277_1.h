int d_ = 0;
unsigned char board_[(19 + 2) *(19 + 1) + 1];
int ii_ = 45;
int delta_[8];
char safe_[(19 + 1) *(19 + 1)];
int deltai_[8];
int delta_i_ = 0;
int deltaj_[8];
int delta_j_ = 0;
int queue_start_ = 1;
int permeability_array_[(19 + 1) *(19 + 1)];
int current_strength_ = 170600;
int b_ = 4096;
int working_[20 * 20];
int queue_[20 * 20];
int queue_end_ = 1;
