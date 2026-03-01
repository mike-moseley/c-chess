#pragma once
#include "pieces.h"
#include <ncurses.h>

extern int BOARD_BG_WHITE;
extern int BOARD_BG_BLACK;
extern int LINE_COLOR;

typedef struct Cell {
	piece_t *piece;
	int can_move;
} cell_t;

typedef struct Board {
	int height;
	int width;
	cell_t **cells;
} board_t;

void draw_board(WINDOW *window, board_t *board);
board_t *new_board(int height, int width);
