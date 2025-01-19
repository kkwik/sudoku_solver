#include "solver.h"
#include "cell.h"
#include "board.h"
#include "sudoku_queue.h"

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

void split(struct sudoku_q *q, struct sudoku_board *board) {
	int i = 0;
	// Fast forward to an interesting cell
	while (count_candidates(board->cells[i / 9][i % 9]) == 1) {
		i++;
	}

	int r = i / 9;
	int c = i % 9;

	int candidate_count = count_candidates(board->cells[r][c]);
	if (candidate_count == 0) {
		// No possible options for this cell, must be invalid
		return;
	}

	int cell = board->cells[r][c];	

	for (int j = 0; j < candidate_count; j++) {
		// Create a copy of the current board
		struct sudoku_board *temp = malloc(sizeof(struct sudoku_board));
		copy_board(board, temp);	

		// Assign the board one of the valid candidates and queue it
		int candidate = get_first_candidate(cell);
		cell = clear_candidate(cell, candidate);
		temp->cells[r][c] = put_candidate(0, candidate);
		q_queue(q, temp);

	}
}

struct sudoku_board *solve(struct sudoku_board *board_input) {
	struct sudoku_q q;
	q_init(&q, 10);
	q_queue(&q, board_input);
	bool solved = false;
	size_t max_count = 0;

	do {
		if (q_empty(&q)) {
			return NULL;
		}
		struct sudoku_board *board;
		q_dequeue(&q, &board);

		eval_rules(board);

		if (!completeBoard(board)) {
			// We've evaluated rules as much as possible, make a guess and try
			split(&q, board);
			max_count = max_count > q_count(&q) ? max_count : q_count(&q);
		} else {
			board_input = board;
			solved = true;
		}
	} while (!solved);
	printf("Queue expanded to hold a maximum of %zu boards\n", max_count);

	q_dealloc(&q);
	return board_input;
}

