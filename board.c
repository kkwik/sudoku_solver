#include "board.h"
#include "cell.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"

#define FORMAT_BOLD "\x1b[1m"
#define FORMAT_OFF "\x1b[22m"

bool rowHas(int board[9][9], int r, int val, int skipC) {
	for (int c = 0; c < 9; c++) {
		if (c == skipC) {
			continue;
		}

		if (has_candidate(board[r][c], val) && count_candidates(board[r][c]) == 1) {
			return true;
		}
	}
	return false;
}

bool colHas(int board[9][9], int c, int val, int skipR) {
	for (int r = 0; r < 9; r++) {
		if (r == skipR) {
			continue;
		}

		if (has_candidate(board[r][c], val) && count_candidates(board[r][c]) == 1) {
			return true;
		}
	}
	return false;
}

bool sqrHas(int board[9][9], int ir, int ic, int val) {
	int sqr_index = ((ir / 3) * 3) + (ic / 3);
	int sqr_row_offset = 3 * (sqr_index / 3);
	int sqr_col_offset = 3 * (sqr_index % 3);

	for (int i = 0; i < 9; i++) {
		int r = sqr_row_offset + (i / 3);
		int c = sqr_col_offset + (i % 3);

		if (r == ir && c == ic) {
			continue;
		}

		if (has_candidate(board[r][c], val) && count_candidates(board[r][c]) == 1) {
			return true;
		}
	}
	return false;
}

bool cannot_place(int board[9][9], int r, int c, int val) {
	return rowHas(board, r, val, c) || colHas(board, c, val, r) || sqrHas(board, r, c, val);
}

bool validBoard(struct sudoku_board *board) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			int cell = board->cells[r][c];
			if (count_candidates(cell) == 1) {
				int candidate = get_first_candidate(cell);
				if (cannot_place(board->cells, r, c, candidate)) {
					printf("Invalid state: [%d, %d] is %d but %d is present elsewhere in the same row/col/sqr\n", r, c, candidate, candidate);
					return false;	
				}
			} else {
				continue;
			}
		}
	}
	return true;
}

bool completeBoard(struct sudoku_board *board) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			int cell = board->cells[r][c];
			if (count_candidates(cell) != 1) {
				return false;
			}
		}
	}

	return validBoard(board);
}

// Parse board from string
// Returns NULL if an issue is encountered
struct sudoku_board *parse_board(char const *boardStr) {

	if (strlen(boardStr) != 81) {
		printf("Incorrect board input size: 81 inputs needed, %lu provided\n", strlen(boardStr));
		return NULL;
	}

	for (int i = 0, c = boardStr[0] - '0'; i < 81; i++, c = boardStr[i] - '0') {
		if (c < 0 || c > 9) {
			printf("Invalid board input: inputs must be 0 - 9\n");
			return NULL;
		}
	}
	// Load board
	struct sudoku_board *temp = malloc(sizeof(struct sudoku_board));
	if (temp == NULL) {
		return NULL;
	}

	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		int val = boardStr[i] - '0';

		if (val == 0) {
			temp->cells[r][c] = ALL_CANDIDATES;
		} else {
			temp->cells[r][c] = put_candidate(0, val);
		}
	}

	if (!validBoard(temp)) {
		printf("Invalid board provided\n");
		return NULL;
	}
	return temp;
}

void copy_board(struct sudoku_board const *original, struct sudoku_board *copy) {
	*copy = *original;
}

void populate_board(struct sudoku_board *board, int val) {
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		board->cells[r][c] = val;
	}
}

void printBoard(struct sudoku_board const *board) {
	printf("    0 1 2   3 4 5   6 7 8\n");
	printf("  -------------------------\n");
	for (int r = 0; r < 9; r++) {
		if (r != 0 && r % 3 == 0) {
			printf("  |-------+-------+-------|\n");
		}

		printf("%d ", r);

		for (int c = 0; c < 9; c++) {
			if (c % 3 == 0) {
				printf("| ");
			}

			int cell = board->cells[r][c];
			if (count_candidates(cell) == 1) {
				printf(FORMAT_BOLD "%d" FORMAT_OFF " ", get_first_candidate(cell));
			} else {
				printf("  ");
			}

			if (c == 8) {
				printf("|\n");
			}
		}
	}
	printf("  -------------------------\n");
}
