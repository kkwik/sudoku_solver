#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stddef.h>

struct sudoku_board {
	int cells[9][9];
};
void printBoard(struct sudoku_board *board);
struct sudoku_board* parseBoardString(struct sudoku_board *board, char *boardStr);
bool rowHas(int board[9][9], int r, int val, int skipC);
bool colHas(int board[9][9], int c, int val, int skipR);
bool sqrHas(int board[9][9], int ir, int ic, int val);
bool cannot_place(int board[9][9], int r, int c, int val);
bool validBoard(struct sudoku_board *board);
bool completeBoard(struct sudoku_board *board);

#endif
