#include "state.h"

#include <stdbool.h>
#include <stdio.h>

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

void evalBoard(struct sudoku_board *state) {
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		printf("Evaluating [%d, %d]:\n", r, c);
		
	}
}

void parseBoardString(struct sudoku_board *game_state, char *boardStr) {
	// Load board
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		game_state->board[r][c] = boardStr[i] - '0';
		game_state->readonly[r][c] = boardStr[i] - '0' == 0 ? 0 : 1;

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
