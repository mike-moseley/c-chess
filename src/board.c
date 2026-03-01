#include "board.h"
#include <stdlib.h>

board_t *new_board(int height, int width) {
	int size = height * width;
	cell_t **cells = calloc(size, sizeof(cell_t *));
	board_t *board = calloc(size, sizeof(board_t));
	board->cells = cells;
	board->height = height;
	board->width = width;
	return board;
}
