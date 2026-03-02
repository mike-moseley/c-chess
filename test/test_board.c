#include "unity.h"
#include "board.h"

void setUp(void) {}
void tearDown(void) {}

void test_coord_to_index() {
	board_t *board = new_board(8, 8);
	TEST_ASSERT_EQUAL(0, coord_to_index(0,0, board));
	TEST_ASSERT_EQUAL(1, coord_to_index(0,1, board));
	TEST_ASSERT_EQUAL(9, coord_to_index(1,1, board));
	TEST_ASSERT_EQUAL(63, coord_to_index(7,7, board));
	free_board(board);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_coord_to_index);
	return UNITY_END();
}
