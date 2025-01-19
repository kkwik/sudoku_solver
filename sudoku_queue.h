#ifndef SUDOKU_QUEUE_H
#define SUDOKU_QUEUE_H

#include "board.h"
#include <stddef.h>
#include <stdlib.h>

struct sudoku_q {
	struct sudoku_board **buffer;
	struct sudoku_board **buffer_end;
	struct sudoku_board **head;
	struct sudoku_board **tail;
	size_t count;
	size_t capacity;
};
void q_init(struct sudoku_q *q, size_t initial_size);
void q_dealloc(struct sudoku_q *q);
bool q_empty(struct sudoku_q *q);
size_t q_capacity(struct sudoku_q *q);
size_t q_count(struct sudoku_q *q);
void q_queue(struct sudoku_q *q, struct sudoku_board *board);
void q_dequeue(struct sudoku_q *q, struct sudoku_board **board);
void q_print(struct sudoku_q *q);

#endif
