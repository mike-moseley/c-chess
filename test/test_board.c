#include "unity.h"
#include "board.h"

void setUp(void) {}
void tearDown(void) {}

void test_coord_to_index() {
	board_t *board = new_board(8, 8);
	TEST_ASSERT_EQUAL(0, coord_to_index(board, 0,0));
	TEST_ASSERT_EQUAL(1, coord_to_index(board, 0,1));
	TEST_ASSERT_EQUAL(9, coord_to_index(board, 1,1));
	TEST_ASSERT_EQUAL(63, coord_to_index(board, 7,7));
	free_board(board);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_coord_to_index);
	return UNITY_END();
}
