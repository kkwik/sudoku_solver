
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void parseBoardString(int board[9][9], char *boardStr) {
	for (int i = 0; i < 81; i++) {
		int r = i / 9;
		int c = i % 9;

		board[r][c] = boardStr[i] - '0';
	}
}

char getInput() {
	char input = fgetc(stdin);

	// Clear stdin
	char c;
	while ((c = getchar()) != '\n' && c != EOF) { }

	return input;
}

void printBoard(int board[9][9]) {
	printf("-------------------------\n");
	for (int r = 0; r < 9; r++) {
		if (r != 0 && r % 3 == 0) {
			printf("|-------+-------+-------|\n");
		}

		for (int c = 0; c < 9; c++) {
			if (c % 3 == 0) {
				printf("| ");
			}
			printf("%d ", board[r][c]);

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

int main(int argc, char **argv) {
	
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return EXIT_FAILURE;
	}

	char* boardInput = *(argv + 1);

	if (strlen(boardInput) != 81) {
		printf("Incorrect board input size: 81 inputs needed, %lu provided\n", strlen(boardInput));
	}

	int (*board)[9] = malloc(81 * sizeof(int));
	parseBoardString(board, boardInput);

	char input = ' ';
	do {
		input = ' ';

		printf("\n");
		printBoard(board);
		printf("\n");
		printf("Select Action: \n"
			"\tq: Exit\n"
			"\te: Edit\n"
			"> "
		);

		input = getInput(); 

		// Handle input
		switch (input) {
			case 'q':
				free(board);
				break;
			case 'e':
				printf("Row to modify: ");
				int row = getInput() - '0';
				if (row < 0 || row > 8) {
					break;
				}

				printf("Col to modify: ");
				int col = getInput() - '0';
				if (col < 0 || col > 8) {
					break;
				}

				printf("New value: ");
				int newVal = getInput() - '0';
				if (newVal < 0 || newVal > 8) {
					break;
				}

				board[row][col] = newVal;
				break;
			default:
				printf("Invalid option: %c\n", input);
				break;
		}

	} while (input != 'q');
}
