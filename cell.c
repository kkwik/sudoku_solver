#include <stdbool.h>
#include <stdio.h>

bool has_candidate(int cell, int candidate) {
	return (cell >> (candidate - 1)) & 1;
}

int put_candidate(int cell, int candidate) {
	return cell | (1 << (candidate - 1));	
}

int clear_candidate(int cell, int candidate) {
	return cell & ~(1 << (candidate - 1));
}

int count_candidates(int cell) {
	int counter = 0;
	for (int candidate = 1; candidate < 10; candidate++) {
		counter += has_candidate(cell, candidate);	
	}
	return counter;
}

// Will return the first/lowest candidate available
int get_first_candidate(int cell) {
	for (int candidate = 1; candidate < 10; candidate++) {
		if (has_candidate(cell, candidate)) {
			return candidate;
		}
	}
	return 0;
}

void print_candidates(int cell) {
	for (int candidate = 1; candidate < 10; candidate++) {
		if (has_candidate(cell, candidate)) {
			printf("%d ", candidate);
		}
	}
	printf("\n");	
}
