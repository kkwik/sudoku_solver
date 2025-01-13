#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stddef.h>

struct sudoku_board {
	int board[9][9];
	int readonly[9][9];
};
void printCandidates(int cand);
void evalBoard(struct sudoku_board *state);
void parseBoardString(struct sudoku_board *game_state, char *boardStr);
void printBoard(struct sudoku_board *game_state);
bool rowHas(int board[9][9], int r, int val);
bool colHas(int board[9][9], int c, int val);
bool sqrHas(int board[9][9], int sqrI, int val);

#endif
