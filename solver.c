#include "solver.h"
#include "cell.h"

#include <stdbool.h>
#include <stdio.h>
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

void printBoard(struct sudoku_board *game_state) {
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

			bool readonly = game_state->readonly[r][c];
			int cell = game_state->board[r][c];
			if (count_candidates(cell) == 1) {
				if (readonly) {
					printf(FORMAT_BOLD "%d" FORMAT_OFF " ", get_first_candidate(cell));
				} else {
					printf("%d ", get_first_candidate(cell));
				}
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

bool validBoard(struct sudoku_board *state) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			int cell = state->board[r][c];
			if (count_candidates(cell) == 1) {
				int candidate = get_first_candidate(cell);
				if (rowHas(state->board, r, candidate, c) ||
					colHas(state->board, c, candidate, r) ||
					sqrHas(state->board, r, c, candidate)) {
					printf("Invalid state at [%d, %d] which is %d\n", r, c, candidate);
					return false;	
				}
			} else {
				continue;
			}
		}
	}
	return true;
}

bool completeBoard(struct sudoku_board *state) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			int cell = state->board[r][c];
			if (count_candidates(cell) != 1) {
				return false;
			}
		}
	}

	return validBoard(state);
}

void evalSimpleRules(struct sudoku_board *state) {
	bool changed = false;
	do {
		changed = false;
		for (int i = 0; i < 81; i++) {
			int r = i / 9;
			int c = i % 9;

			if (state->readonly[r][c] == 1 || count_candidates(state->board[r][c]) == 1) {
				continue;
			}

			// Unpack candidates to array
			for (int candidate = 1; candidate < 10; candidate++) {
				if (has_candidate(state->board[r][c], candidate)) {
					if (rowHas(state->board, r, candidate, c) || 
						colHas(state->board, c, candidate, r) ||
						sqrHas(state->board, r, c, candidate)) {
						state->board[r][c] = clear_candidate(state->board[r][c], candidate);
						changed = true;
					}
				}
			}
		}

		if (!validBoard(state)) {
			printf("Invalid board state!\n");
			printBoard(state);
			assert(false);
		}
	} while (changed);
}

void evalBoard(struct sudoku_board *state) {
	evalSimpleRules(state);
}

void parseBoardString(struct sudoku_board *game_state, char *boardStr) {
	// Load board
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		int val = boardStr[i] - '0';

		if (val == 0) {
			game_state->board[r][c] = ALL_CANDIDATES;
			game_state->readonly[r][c] = 0; 
		} else {
			game_state->board[r][c] = put_candidate(0, val);
			game_state->readonly[r][c] = 1;
		}
	}

	// Run initial evaluation of board
	//evalBoard(game_state);
}

