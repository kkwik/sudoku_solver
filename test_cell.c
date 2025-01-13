#include "cell.h"
#include "assert.h"
#include "test_cell.h"

void test_has_candidate_none() {
	int cell = 0;

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_1() {
	int cell = 1;	

	assert(has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_2() {
	int cell = 2;	

	assert(!has_candidate(cell, 1));	
	assert(has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_3() {
	int cell = 4;	

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_4() {
	int cell = 8;	

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_5() {
	int cell = 16;	

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_6() {
	int cell = 32;	

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_7() {
	int cell = 64;	

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_8() {
	int cell = 128;

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_has_candidate_9() {
	int cell = 256;

	assert(!has_candidate(cell, 1));	
	assert(!has_candidate(cell, 2));	
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(has_candidate(cell, 9));	
}

void test_has_candidate_1_2() {
	int cell = 3;
	
	assert(has_candidate(cell, 1));
	assert(has_candidate(cell, 2));
	assert(!has_candidate(cell, 3));	
	assert(!has_candidate(cell, 4));	
	assert(!has_candidate(cell, 5));	
	assert(!has_candidate(cell, 6));	
	assert(!has_candidate(cell, 7));	
	assert(!has_candidate(cell, 8));	
	assert(!has_candidate(cell, 9));	
}

void test_put_candidate_1() {
	int cell = 0;

	cell = put_candidate(cell, 1);

	assert(cell == 1);
}

void test_put_candidate_5() {
	int cell = 0;

	cell = put_candidate(cell, 5);

	assert(cell == 16);
}

void test_put_candidate_1_2() {
	int cell = 0;

	cell = put_candidate(cell, 1);
	cell = put_candidate(cell, 2);

	assert(cell == 3);
}

void test_clear_candidate_1() {
	int cell = 1;

	cell = clear_candidate(cell, 1);

	assert(cell == 0);
}

void test_clear_candidate_1_2() {
	int cell = 3;

	cell = clear_candidate(cell, 1);
	assert(cell == 2);
	
	cell = clear_candidate(cell, 2);
	assert(cell == 0);
}


void test_count_candidates() {
	assert(count_candidates(0) == 0);

	assert(count_candidates(1) == 1);
	assert(count_candidates(2) == 1);
	assert(count_candidates(4) == 1);
	assert(count_candidates(8) == 1);
	assert(count_candidates(16) == 1);
	assert(count_candidates(32) == 1);
	assert(count_candidates(64) == 1);
	assert(count_candidates(128) == 1);
	assert(count_candidates(256) == 1);

	assert(count_candidates(ALL_CANDIDATES) == 9);
}

 void run_cell_tests() {
	test_has_candidate_none();
	test_has_candidate_1();
	test_has_candidate_2();
	test_has_candidate_3();
	test_has_candidate_4();
	test_has_candidate_5();
	test_has_candidate_6();
	test_has_candidate_7();
	test_has_candidate_8();
	test_has_candidate_9();
	test_has_candidate_1_2();
	test_put_candidate_1();
	test_put_candidate_5();
	test_put_candidate_1_2();
	test_clear_candidate_1();
	test_clear_candidate_1_2();
	test_count_candidates();
}

