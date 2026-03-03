#pragma once
#include "moves.h"
#include <ncurses.h>

extern int BOARD_BG_WHITE;
extern int BOARD_BG_BLACK;
extern int WHITE_COLOR;
extern int BLACK_COLOR;
extern int LINE_COLOR;

typedef struct Cell {
	struct Piece *piece;
} cell_t;

typedef struct Board {
	int height;
	int width;
	cell_t **cells;
} board_t;

void draw_board(WINDOW *window, board_t *board);
board_t *new_board(int height, int width);
void free_board(board_t *board);
int coord_to_index(board_t *board, int y, int x);
vec2_t index_to_coord(board_t *board, int idx);
void add_pieces_to_cells(board_t *board, struct Piece *pieces[16]);
int check_bounds(board_t *board, int y, int x);
