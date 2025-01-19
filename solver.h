#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/queue.h>


struct sudoku_board *solve(struct sudoku_board *board);

#endif
