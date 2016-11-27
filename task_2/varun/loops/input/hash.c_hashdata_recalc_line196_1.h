int pos_ = 0;
unsigned char board_[(19 + 2) *(19 + 1) + 1];
int i_ = 0;
unsigned long target_hashval_[((unsigned long )64) /(((unsigned long )8) * sizeof(long ))];
unsigned long white_hash_[(19 + 1) *(19 + 1)][((unsigned long )64) /(((unsigned long )8) * sizeof(long ))];
unsigned long black_hash_[(19 + 1) *(19 + 1)][((unsigned long )64) /(((unsigned long )8) * sizeof(long ))];
