#include "state.h"

#include <stdbool.h>
#include <stdio.h>

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

bool rowHas(int board[9][9], int r, int val) {
	for (int c = 0; c < 9; c++) {
		if (board[r][c] == val) {
			return true;
		}
	}
	return false;
}

bool colHas(int board[9][9], int c, int val) {
	for (int r = 0; r < 9; r++) {
		if (board[r][c] == val) {
			return true;
		}
	}
	return false;
}

bool sqrHas(int board[9][9], int sqrI, int val) {
	int sqrRI, sqrCI;
	sqrRI = sqrI / 3;
	sqrCI = sqrI % 3;

	for (int i = 0; i < 9; i++) {
		int r = (3 * sqrRI) + (i / 3);
		int c = (3 * sqrCI) + (i % 3);

		if (board[r][c] == val) {
			return true;
		}
	}
	return false;
}

void printCandidates(int cand) {
	for (int i = 1, mask = 1; i < 10; i++, mask <<= 1) {
		if (cand & mask) {
			printf("%d, ", i);
		}
	}
	printf("\n");
}

void evalBoard(struct sudoku_board *state) {
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		if (state->readonly[r][c] == 1) {
			continue;
		}
		int sqrI = ((r / 3) * 3) + (c / 3);
		int candidates = state->candidates[r][c];

		printf("Evaluating [%d, %d]:\n", r, c);

		// Unpack candidates to array
		int cand_arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		for (int j = 1, mask = 1; j < 10; j++, mask <<= 1) {
			if (!(candidates & mask)) {
				cand_arr[j - 1] = 0;		
			}
		}

		for (int j = 1; j < 10; j++) {
			if (rowHas(state->board, r, j) || colHas(state->board, c, j) || sqrHas(state->board, sqrI, j)) {
				cand_arr[j - 1] = 0;
				printf("\tEliminated %d as a candidate\n", j);
			}
		}

		int newCandidates = 0;
		for (int j = 1, mask = 1; c < 10; c++, mask <<= 1) {
			if (cand_arr[j - 1] != 0) {
				newCandidates |= 1;
			}
			newCandidates <<= 1;
		}
		state->candidates[r][c] = newCandidates;

		printCandidates(state->candidates[r][c]);	
		printf("\n");
	}
}

void parseBoardString(struct sudoku_board *game_state, char *boardStr) {
	// Load board
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		game_state->board[r][c] = boardStr[i] - '0';
		game_state->readonly[r][c] = boardStr[i] - '0' == 0 ? 0 : 1;
		game_state->candidates[r][c] = 511;
	}

	// Run initial evaluation of board
	evalBoard(game_state);
}

void printBoard(struct sudoku_board *game_state) {
	printf("-------------------------\n");
	for (int r = 0; r < 9; r++) {
		if (r != 0 && r % 3 == 0) {
			printf("|-------+-------+-------|\n");
		}

		for (int c = 0; c < 9; c++) {
			if (c % 3 == 0) {
				printf("| ");
			}

			bool readonly = game_state->readonly[r][c];
			int val = game_state->board[r][c];
			if (val != 0) {
				if (readonly) {
					printf(COLOR_BOLD "%d" COLOR_OFF " ", val);
				} else {
					printf("%d ", val);
				}
			} else {
				printf("  ");
			}

			if (c == 8) {
				printf("|\n");
			}
		}
	}
	printf("-------------------------\n");
}

