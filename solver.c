#include "solver.h"
#include "cell.h"
#include "board.h"

#include <stdbool.h>
#include <stdio.h>
#include "assert.h"

#include <sys/queue.h>

void eval_rules(struct sudoku_board *board) {
	bool changed = false;
	do {
		changed = false;
		for (int i = 0; i < 81; i++) {
			int r = i / 9;
			int c = i % 9;

			if (count_candidates(board->cells[r][c]) == 1) {
				continue;
			}

			// Unpack candidates to array
			for (int candidate = 1; candidate < 10; candidate++) {
				if (has_candidate(board->cells[r][c], candidate)) {
					if (cannot_place(board->cells, r, c, candidate)) {
						board->cells[r][c] = clear_candidate(board->cells[r][c], candidate);
						changed = true;
					}
				}
			}
		}

		if (!validBoard(board)) {
			printf("Invalid board state!\n");
			printBoard(board);
			assert(false);
		}
	} while (changed);
}

void split(struct sudoku_board *state) {
	(void)state;
	// Malloc one board with one option
	// Malloc another baord with another option
	// ...
	//
	// Add pointer to board in shared queue
}

struct sudoku_board* solve(struct sudoku_board *state) {
	eval_rules(state);

	if (!completeBoard(state)) {
		split(state);
	}
	return NULL;
}

