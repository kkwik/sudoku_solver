#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stddef.h>

struct sudoku_board {
	int cells[9][9];
};
bool rowHas(int board[9][9], int r, int val, int skipC);
bool colHas(int board[9][9], int c, int val, int skipR);
bool sqrHas(int board[9][9], int ir, int ic, int val);
bool cannot_place(int board[9][9], int r, int c, int val);
bool validBoard(struct sudoku_board *board);
bool completeBoard(struct sudoku_board *board);
struct sudoku_board *parse_board(char const *boardStr);
void copy_board(struct sudoku_board const *original, struct sudoku_board *copy);
void populate_board(struct sudoku_board *board, int val);
void printBoard(struct sudoku_board const *board);

#endif
