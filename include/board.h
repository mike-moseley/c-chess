#pragma once
#include "pieces.h"
#include <ncurses.h>

extern int BOARD_BG_WHITE;
extern int BOARD_BG_BLACK;
extern int LINE_COLOR;

typedef struct Cell {
	piece_t *piece;
	int is_occupied;
} cell_t;

typedef struct Board {
	int height;
	int width;
	cell_t **cells;
} board_t;

void draw_board(WINDOW *window, board_t *board);
board_t *new_board(int height, int width);
void free_board(board_t *board);
int coord_to_index(int y, int x, board_t *board);
