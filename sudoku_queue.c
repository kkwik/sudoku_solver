#include "sudoku_queue.h"
#include "board.h"
#include <stdio.h>

struct sudoku_board **wrap_ptr(struct sudoku_board **ptr, struct sudoku_board **buffer_start, struct sudoku_board **buffer_end) {
	if (ptr >= buffer_end) {
		return buffer_start;
	}
	return ptr;
}

void expand(struct sudoku_q *q) {
	int current_capacity = q->buffer_end - q->buffer;
	int new_capacity = 2 * current_capacity;

	struct sudoku_board **temp_buffer = calloc(new_capacity, sizeof(struct sudoku_board *));
	struct sudoku_board **temp_ptr = temp_buffer;

	// Copy over existing values
	// Dowhile because head == tail must already be true
	do {
		*temp_ptr = *q->head;	
		temp_ptr++;
		q->head++;

		// Wrap head if necessary
		q->head = wrap_ptr(q->head, q->buffer, q->buffer_end);	
	} while (q->head != q->tail); 
	
	// Set q pointers to new buffer
	q->buffer = temp_buffer;
	q->buffer_end = q->buffer + new_capacity; 
	q->head = q->buffer;
	q->tail = temp_ptr;
}


void q_init(struct sudoku_q *q, size_t initial_size) {
	if ((q->buffer = calloc(initial_size, sizeof(struct sudoku_board *))) == NULL) {
		printf("Failed to allocate sudoku queue");
		q = NULL;
	}

	q->buffer_end = q->buffer + initial_size;
	q->head = q->buffer;
	q->tail = q->buffer;
}

void q_dealloc(struct sudoku_q *q) {
	free(q->buffer);
	q->buffer = NULL;
	q->buffer_end = NULL;
	q->head = NULL;
	q->tail = NULL;
}

bool q_empty(struct sudoku_q *q) {
	// The only reason the head should == the tail is if we are empty
	// This relies upon expanding automatically if the tail reaches the head
	return q->head == q->tail;
}

int q_capacity(struct sudoku_q *q) {
	return q->buffer_end - q->buffer;
}

void q_queue(struct sudoku_q *q, struct sudoku_board *board) {

	*q->tail = board;
	q->tail++;

	// Wrap tail if necessary
	q->tail = wrap_ptr(q->tail, q->buffer, q->buffer_end);

	// Hit capacity, expand
	if (q->tail == q->head) {
		expand(q);
	} 
}

void q_dequeue(struct sudoku_q *q, struct sudoku_board **board) {
	(void)board; // stop gcc warning
	// Head reached tail, empty
	if (q->head == q->tail) {
		board = NULL;
	}

	*board = *q->head;
	q->head++;

	// Wrap head if necessary
	q->head = wrap_ptr(q->head, q->buffer, q->buffer_end);
}

void q_print(struct sudoku_q *q) {
	int buffer_size = q->buffer_end - q->buffer;
	printf("Queue Status\n");
	printf("Buffer: [%p]\n", (void *)q->buffer);
	printf("Buffer end: [%p]\n", (void *)q->buffer_end);
	printf("Capacity: %d\n", buffer_size);

	printf("Head: [%p]\n", (void *)q->head);
	printf("Tail: [%p]\n", (void *)q->tail);

	for (int i = 0; i < buffer_size; i++) {
		printf("%c%c | %d: [%p] -> [%p]\n", q->head == (q->buffer + i) ? 'H' : ' ', q->tail == (q->buffer + i) ? 'T' : ' ', i, (void *)(q->buffer + i), (void *)*(q->buffer + i));
	}
	printf("\n");
}
