#include "state.h"
#include "cell.h"

#include <stdbool.h>
#include <stdio.h>

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

bool sqrHas(int board[9][9], int sqrI, int val, int skipR, int skipC) {
	int sqrRI, sqrCI;
	sqrRI = sqrI / 3;
	sqrCI = sqrI % 3;

	for (int i = 0; i < 9; i++) {
		int r = (3 * sqrRI) + (i / 3);
		int c = (3 * sqrCI) + (i % 3);

		if (r == skipR && c == skipC) {
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
			int val = game_state->board[r][c];
			if (count_candidates(val) == 1) {
				if (readonly) {
					printf(FORMAT_BOLD "%d" FORMAT_OFF " ", get_first_candidate(val));
				} else {
					printf("%d ", get_first_candidate(val));
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

bool evalSimpleRules(struct sudoku_board *state) {
	bool changed = false;

	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		if (state->readonly[r][c] == 1 || count_candidates(state->board[r][c]) == 1) {
			continue;
		}
		int sqrI = ((r / 3) * 3) + (c / 3);

		// Unpack candidates to array
		for (int candidate = 1; candidate < 10; candidate++) {
			if (has_candidate(state->board[r][c], candidate)) {
				if (rowHas(state->board, r, candidate, c) || colHas(state->board, c, candidate, r) || sqrHas(state->board, sqrI, candidate, r, c)) {
					state->board[r][c] = clear_candidate(state->board[r][c], candidate);
					changed = true;
				}
			}
		}
	}

	return changed;
}

void evalBoard(struct sudoku_board *state) {
	printf("Evaluation started\n");
	bool changed = false;
	do {
		changed = evalSimpleRules(state);
		if (changed) {
			printBoard(state);
		}
	} while (changed);

	printf("Evaluation complete\n");
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

