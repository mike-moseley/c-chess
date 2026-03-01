#pragma once
#import "pieces.h"

typedef struct Cell {
	piece_t *piece;
	int can_move;
} cell_t;

typedef struct Board {
	int height;
	int width;
	cell_t **cells;
} board_t;
