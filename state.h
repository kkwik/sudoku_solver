#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stddef.h>

struct sudoku_board {
	int board[9][9];
	int readonly[9][9];
};
void printBoard(struct sudoku_board *game_state);
void evalBoard(struct sudoku_board *state);
void parseBoardString(struct sudoku_board *game_state, char *boardStr);

#endif
