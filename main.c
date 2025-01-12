
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int* parseBoardString(int *board, char *boardStr) {
	for (int i = 0; i < 81; i++) {
		*(board + i) = boardStr[i] - '0';
	}
	return board;
}

int boardVal(int *board, int rowI, int colI) {
	return *(board + (9 * rowI) + colI);
}

void printBoard(int *board) {
	printf("-------------------------\n");
	for (int i = 0; i < 9; i++) {
		if (i != 0 && i % 3 == 0) {
			printf("|-------+-------+-------|\n");
		}

		printf("| %d %d %d | %d %d %d | %d %d %d |\n", boardVal(board, i, 0), boardVal(board, i, 1), boardVal(board, i, 2), boardVal(board, i, 3), boardVal(board, i, 4), boardVal(board, i, 5), boardVal(board, i, 6), boardVal(board, i, 7), boardVal(board, i, 8));
	}
	printf("-------------------------\n");
}

bool rowHas(int *board, int rowI, int val) {
	for (int colI = 0; colI < 9; colI++) {
		if (boardVal(board, rowI, colI) == val) {
			return true;
		}
	}
	return false;
}

bool colHas(int *board, int colI, int val) {
	for (int rowI = 0; rowI < 9; rowI++) {
		if (boardVal(board, rowI, colI) == val) {
			return true;
		}
	}
	return false;
}

bool sqrHas(int *board, int sqrI, int val) {
	int sqrRI, sqrCI;
	sqrRI = sqrI / 3;
	sqrCI = sqrI % 3;

	for (int i = 0; i < 9; i++) {
		int rowI, colI;

		rowI = (3 * sqrRI) + (i / 3);
		colI = (3 * sqrCI) + (i % 3);

		if (boardVal(board, rowI, colI) == val) {
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

	int *board = malloc(81 * sizeof(int));
	parseBoardString(board, boardInput);

	printBoard(board);
}
