#pragma once
#include "pieces.h"
#include <ncurses.h>

extern int BOARD_BG_WHITE;
extern int BOARD_BG_BLACK;
extern int WHITE_COLOR;
extern int BLACK_COLOR;
extern int LINE_COLOR;

typedef struct Cell {
	piece_t *piece;
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
piece_t *new_piece(piece_kind_t kind, chess_color_t color, int y, int x, vec2_t *moves);
void init_white_pieces_classic(board_t *board, piece_t *pieces[16]);
void init_black_pieces_classic(board_t *board, piece_t *pieces[16]);
piece_t **create_pieces(board_t *board);
void add_pieces_to_cells(board_t *board, piece_t *pieces[16]);
