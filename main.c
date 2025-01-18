#include "solver.h"
#include "board.h"
#include "cell.h"
#include "test_cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


char getInput() {
	char input = fgetc(stdin);

	// Clear stdin
	char c;
	while ((c = getchar()) != '\n' && c != EOF) { }

	return input;
}

int main(int argc, char **argv) {

	run_cell_tests();
	
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return EXIT_FAILURE;
	}

	char* boardInput = *(argv + 1);


	struct sudoku_board *board = malloc(sizeof(struct sudoku_board));
	board = parseBoardString(board, boardInput);

	if (board == NULL) {
		return EXIT_FAILURE;
	}

	char input = ' ';
	do {
		input = ' ';

		printf("\n");
		printBoard(board);
		printf("\n");
		printf("Select Action: \n"
			"\tq: Exit\n"
			"\te: Evaluate one step of the board state\n"
			"\ti: Inspect cell candidates\n"
			"> "
		);

		input = getInput(); 

		// Handle input
		switch (input) {
			case 'q':
				break;
			case 'e':
				solve(board);
				break;
			case 'i':
			{
				printf("Input row: ");
				int row = getInput() - '0';
				if (row < 0 || row > 9) {
					printf("Row must be 0 - 9, %d given\n", row);
					break;
				}

				printf("Input col: ");
				int col = getInput() - '0';
				if (col < 0 || col > 9) {
					printf("Col must be 0 - 9, %d given\n", col);
					break;
				}
					
				print_candidates(board->cells[row][col]);
				printf("%d\n", board->cells[row][col]);
				break;
			}
			default:
				printf("Invalid option: %c\n", input);
				break;
		}

	} while (input != 'q');
}
