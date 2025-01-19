#include "assert.h"
#include "test_queue.h"
#include "board.h"
#include "sudoku_queue.h"
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

void alloc_dealloc_test() {
	struct sudoku_q q;
	int initial_size = 4;

	q_init(&q, initial_size);

	int capacity = q_capacity(&q);
	assert(capacity == initial_size);

	q_dealloc(&q);
	assert(q.buffer == NULL);
}

void test_empty() {
	struct sudoku_q q;
	struct sudoku_board *b1 = (struct sudoku_board *)1;

	q_init(&q, 4);
	assert(q_empty(&q));

	q_queue(&q, b1);
	assert(!q_empty(&q));
	
	q_dequeue(&q, &b1);
	assert(q_empty(&q));

	q_dealloc(&q);
}

void test_queue_1() {
	struct sudoku_q q;
	struct sudoku_board *b1 = (struct sudoku_board *)1;
	struct sudoku_board *b2 = (struct sudoku_board *)2;

	q_init(&q, 4);
	q_queue(&q, b1);
	q_dequeue(&q, &b2);	

	assert(b1 == b2);
	q_dealloc(&q);
}

void test_multiple_queue() {
	struct sudoku_q q;
	struct sudoku_board *b1 = (struct sudoku_board *)1;
	struct sudoku_board *b2 = (struct sudoku_board *)2;
	struct sudoku_board *b3 = (struct sudoku_board *)3;
	struct sudoku_board *b4 = (struct sudoku_board *)4;

	q_init(&q, 4);

	q_queue(&q, b1);
	q_queue(&q, b2);
	q_dequeue(&q, &b3);	
	q_dequeue(&q, &b4);	

	assert(b1 == b3);
	assert(b2 == b4);
	q_dealloc(&q);
}

void test_expand() {
	struct sudoku_q q;
	int initial_size = 4;
	q_init(&q, initial_size);

	struct sudoku_board *b1 = (struct sudoku_board *)1;
	struct sudoku_board *b2 = (struct sudoku_board *)2;
	struct sudoku_board *b3 = (struct sudoku_board *)3;
	struct sudoku_board *b4 = (struct sudoku_board *)4;

	q_queue(&q, b1);
	q_queue(&q, b2);
	q_queue(&q, b3);
	assert(q_capacity(&q) == initial_size);

	q_queue(&q, b4);
	assert(q_capacity(&q) == 2 * initial_size);


	q_dealloc(&q);
}

void test_wrap() {
	struct sudoku_q q;
	int initial_size = 4;
	q_init(&q, initial_size);

	struct sudoku_board *b1 = (struct sudoku_board *)1;
	struct sudoku_board *b2 = (struct sudoku_board *)2;
	struct sudoku_board *b3 = (struct sudoku_board *)3;
	struct sudoku_board *b4 = (struct sudoku_board *)4;
	struct sudoku_board *b5 = (struct sudoku_board *)5;

	struct sudoku_board *b6 = (struct sudoku_board *)6;
	struct sudoku_board *b7 = (struct sudoku_board *)7;
	struct sudoku_board *b8 = (struct sudoku_board *)8;

	q_queue(&q, b1);
	q_dequeue(&q, NULL);

	q_queue(&q, b2);
	q_dequeue(&q, NULL);

	q_queue(&q, b3);
	q_queue(&q, b4);
	q_queue(&q, b5);
	q_dequeue(&q, &b6);
	q_dequeue(&q, &b7);
	q_dequeue(&q, &b8);
	assert(b3 == b6);
	assert(b4 == b7);
	assert(b5 == b8);
	
	q_dealloc(&q);
}

void test_wrap_and_expand() {
	struct sudoku_q q;
	int initial_size = 4;
	q_init(&q, initial_size);

	struct sudoku_board *b1 = (struct sudoku_board *)1;
	struct sudoku_board *b2 = (struct sudoku_board *)2;
	struct sudoku_board *b3 = (struct sudoku_board *)3;
	struct sudoku_board *b4 = (struct sudoku_board *)4;
	struct sudoku_board *b5 = (struct sudoku_board *)5;
	struct sudoku_board *b6 = (struct sudoku_board *)6;
	struct sudoku_board *b7 = (struct sudoku_board *)7;
	struct sudoku_board *b8 = (struct sudoku_board *)8;
	struct sudoku_board *b9 = (struct sudoku_board *)9;
	struct sudoku_board *b10 = (struct sudoku_board *)10;
	struct sudoku_board *b11 = (struct sudoku_board *)11;
	struct sudoku_board *b12 = (struct sudoku_board *)12;

	q_queue(&q, b1);
	q_dequeue(&q, NULL);

	q_queue(&q, b2);
	q_dequeue(&q, NULL);

	q_queue(&q, b3);
	q_queue(&q, b4);
	q_queue(&q, b5);
	q_queue(&q, b6); // Queue is now full and expanded
	q_queue(&q, b7); 
	q_dequeue(&q, &b8);
	q_dequeue(&q, &b9);
	q_dequeue(&q, &b10);
	q_dequeue(&q, &b11);
	q_dequeue(&q, &b12);
	assert(b3 == b8);
	assert(b4 == b9);
	assert(b5 == b10);
	assert(b6 == b11);
	assert(b7 == b12);

	q_dealloc(&q);
}

void run_queue_tests() {
	alloc_dealloc_test();	
	test_empty();
	test_queue_1();
	test_multiple_queue();
	test_expand();
	test_wrap();
	test_wrap_and_expand();
}
