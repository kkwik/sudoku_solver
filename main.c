#include "cell.h"
#include "solver.h"
#include "test_cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	if (strlen(boardInput) != 81) {
		printf("Incorrect board input size: 81 inputs needed, %lu provided\n", strlen(boardInput));
		return EXIT_FAILURE;
	}

	for (int i = 0, c = boardInput[0] - '0'; i < 81; i++, c = boardInput[i] - '0') {
		if (c < 0 || c > 9) {
			printf("Invalid board input: inputs must be 0 - 9\n");
			return EXIT_FAILURE;
		}
	}

	struct sudoku_board *game_state = malloc(sizeof(struct sudoku_board));


	parseBoardString(game_state, boardInput);

	char input = ' ';
	do {
		input = ' ';

		printf("\n");
		printBoard(game_state);
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
				evalBoard(game_state);
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
					
				print_candidates(game_state->board[row][col]);
				printf("%d\n", game_state->board[row][col]);
				break;
			}
			default:
				printf("Invalid option: %c\n", input);
				break;
		}

	} while (input != 'q');
}
