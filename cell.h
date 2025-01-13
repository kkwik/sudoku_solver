#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

#define ALL_CANDIDATES 511

bool has_candidate(int cell, int candidate);
int put_candidate(int cell, int candidate);
int clear_candidate(int cell, int candidate);
int count_candidates(int cell);
int get_first_candidate(int cell);
void print_candidates(int cell);

#endif
