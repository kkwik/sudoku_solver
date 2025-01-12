
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* parseBoardString(int *board, char *boardStr) {
	for (int i = 0; i < 81; i++) {
		*(board + i) = boardStr[i] - '0';
	}
	return board;
}

void printBoard(int *board) {
	printf("-------------------------\n");
	for(int i = 0; i < 9; i++) {
		if (i != 0 && i % 3 == 0) {
			printf("|-------+-------+-------|\n");
		}

		printf("| %d %d %d | %d %d %d | %d %d %d |\n", *(board + 0), *(board + 1), *(board + 2), *(board + 3), *(board + 4), *(board + 5), *(board + 6), *(board + 7), *(board + 8));
	}
	printf("-------------------------\n");
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

	int *board = malloc(81 * sizeof(int));
	parseBoardString(board, boardInput);

	printBoard(board);
}
