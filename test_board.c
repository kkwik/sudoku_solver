#include "test_board.h"
#include "assert.h"
#include "board.h"

void test_empty_board() {
	struct sudoku_board b1;

	populate_board(&b1, 0);

	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;
		assert(b1.cells[r][c] == 0);	
	}
}

void test_copy_board() {
	struct sudoku_board b1;
	populate_board(&b1, 1);

	struct sudoku_board b2;
	populate_board(&b2, 2);

	copy_board(&b1, &b2);

	// Ensure b1 and b2 aren't pointing to the same thing
	assert(&b1 != &b2);

	b1.cells[0][0] = 3;
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;
		assert(b2.cells[r][c] == 1);	
	}
}

void run_board_tests() {
	test_empty_board();
	test_copy_board();
}
