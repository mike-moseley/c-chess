#pragma once
#include "board.h"
#include "moves.h"
#include "pieces.h"
#include <ncurses.h>
#include <stdlib.h>

int BOARD_BG_WHITE = -1;
int BOARD_BG_BLACK = 3;
int WHITE_COLOR = 12;
int BLACK_COLOR = 4;
int LINE_COLOR = 8;

board_t *
new_board (int height, int width)
{
	int i, size;
	cell_t **cells;
	board_t *board;
	size = height * width;
	cells = calloc (size, sizeof (cell_t *));
	for (i = 0; i < size; i++)
		{
			cells[i] = calloc (1, sizeof (cell_t));
			cells[i]->moveable = 0;
		}
	board = calloc (1, sizeof (board_t));
	board->cells = cells;
	board->height = height;
	board->width = width;
	return board;
}

void
free_board (board_t *board)
{
	cell_t **cells = board->cells;
	int size = board->height * board->width;
	int i;
	for (i = 0; i < size; i++)
		{
			free (cells[i]);
		}
	free (cells);
	free (board);
}

void
clear_board_moveable (board_t *board)
{
	cell_t **cells = board->cells;
	int size = board->height * board->width;
	int i;
	for (i = 0; i < size; i++)
		{
			cells[i]->moveable = 0;
		}
}

int
coord_to_index (board_t *board, int y, int x)
{
	return x + y * board->width;
}

vec2_t *
index_to_coord (board_t *board, int idx)
{
	vec2_t *coord = calloc (1, sizeof (vec2_t));
	coord->x = idx % board->height;
	coord->y = (idx - coord->x) / board->height;
	return coord;
}

int
check_bounds (board_t *board, int y, int x)
{
	return (y >= 0) && (y < board->height) && (x >= 0) && (x < board->width);
}

void
add_pieces_to_cells (board_t *board, piece_t *pieces[16])
{
	int i;
	for (i = 0; i < 16; i++)
		{
			int piece_idx = coord_to_index (board, pieces[i]->y, pieces[i]->x);
			board->cells[piece_idx]->piece = pieces[i];
		}
}
void
draw_board (WINDOW *window, board_t *board, int cursor_y, int cursor_x,
			piece_t *selected)
{
	/*
	// Draw outer borders
	// TODO: replace with border when board window is implemented
	// wborder(window, 0, 0, 0, 0, 0, 0, 0
	*/
	int y;
	int x;
	piece_t *piece;

	attron (COLOR_PAIR (3));
	mvwhline (window, 0, 0, ACS_HLINE, board->width * 2);
	mvwhline (window, board->height * 2, 1, ACS_HLINE, board->width * 2);
	mvwvline (window, 1, 0, ACS_VLINE, board->height * 2);
	mvwvline (window, 1, board->width * 2, ACS_VLINE, board->height * 2);

	mvwaddch (window, 0, 0, ACS_ULCORNER);
	mvwaddch (window, 0, board->width * 2, ACS_URCORNER);
	mvwaddch (window, board->height * 2, 0, ACS_LLCORNER);
	mvwaddch (window, board->height * 2, board->width * 2, ACS_LRCORNER);
	attroff (COLOR_PAIR (3));

	for (y = 0; y <= board->height * 2; y++)
		{
			for (x = 0; x <= board->width * 2; x++)
				{
					/*
					// Cells where lines meet edges
					*/
					attron (COLOR_PAIR (3));
					if ((y == 0) && (x % 2 == 0) && (x != 0)
						&& (x != board->width * 2))
						{
							mvwaddch (window, y, x, ACS_TTEE);
						}
					if ((y == board->height * 2) && (x % 2 == 0) && (x != 0)
						&& (x != board->width * 2))
						{
							mvwaddch (window, y, x, ACS_BTEE);
						}
					if ((x == 0) && (y % 2 == 0) && (y != 0)
						&& (y != board->height * 2))
						{
							mvwaddch (window, y, x, ACS_LTEE);
						}
					if ((x == board->width * 2) && (y % 2 == 0) && (y != 0)
						&& (y != board->height * 2))
						{
							mvwaddch (window, y, x, ACS_RTEE);
						}

					if ((y != 0) && (x != 0) && (y != board->height * 2)
						&& (x != board->width * 2))
						{
							int current_idx
								= coord_to_index (board, y / 2, x / 2);
							/*
							// Cells where lines cross
							*/
							if ((x % 2 == 0) && (y % 2 == 0))
								{
									mvwaddch (window, y, x, ACS_PLUS);
								}
							/*
							// Vertical lines
							*/
							if (y % 2 == 1)
								{
									mvwaddch (window, y, x, ACS_VLINE);
								}
							/*
							// Horizontal lines
							*/
							if (x % 2 == 1)
								{
									mvwaddch (window, y, x, ACS_HLINE);
								}
							attroff (COLOR_PAIR (3));
							/*
							// Every space
							*/
							if ((x % 2 == 1) && (y % 2 == 1))
								{
									mvwaddch (window, y, x, ' ');
								}

							/*
							// Color spaces
							*/
							piece = board->cells[current_idx]->piece;

							/*
							// Color white spaces
							*/
							if (((x % 4 == 3) && (y % 4 == 1))
								|| ((x % 4 == 1) && (y % 4 == 3)))
								{
									if ((piece != NULL)
										&& (piece->color == WHITE))
										{
											mvwaddch (window, y, x,
													  piece->symbol
														  | COLOR_PAIR (5));
										}
									else if ((piece != NULL)
											 && (piece->color == BLACK))
										{
											mvwaddch (window, y, x,
													  piece->symbol
														  | COLOR_PAIR (7));
										}
									else
										{
											mvwaddch (window, y, x,
													  ' ' | COLOR_PAIR (2));
										}
								}

							/*
							// Color black spaces
							*/
							if (((x % 4 == 3) && (y % 4 == 3))
								|| ((x % 4 == 1) && (y % 4 == 1)))
								{
									if ((piece != NULL)
										&& (piece->color == WHITE))
										{
											mvwaddch (window, y, x,
													  piece->symbol
														  | COLOR_PAIR (4));
										}
									else if ((piece != NULL)
											 && (piece->color == BLACK))
										{
											mvwaddch (window, y, x,
													  piece->symbol
														  | COLOR_PAIR (6));
										}
									else
										{
											mvwaddch (window, y, x,
													  ' ' | COLOR_PAIR (1));
										}
								}

							/*
							// Draw cursor and selected square
							*/
							if ((cursor_y == y / 2) && (cursor_x == x / 2))
								{
									mvwchgat (window, cursor_y * 2 + 1,
											  cursor_x * 2 + 1, 1, A_NORMAL, 8,
											  NULL);
								}
							if (selected != NULL)
								{
									if ((selected->y == y / 2)
										&& selected->x == x / 2)
										{
											mvwchgat (window,
													  selected->y * 2 + 1,
													  selected->x * 2 + 1, 1,
													  A_REVERSE, 0, NULL);
										}
								}
						}
				}
		}
	if (selected != NULL)
		{
			int i;
			for (i = 0; i < selected->moves_count; i++)
				{
					vec2_t moves = selected->moves[i];
					if ((moves.y == cursor_y) && (moves.x == cursor_x))
						{
							mvwchgat (window, moves.y * 2 + 1, moves.x * 2 + 1,
									  1, A_NORMAL, 8, NULL);
						}
					else
						{
							mvwchgat (window, moves.y * 2 + 1, moves.x * 2 + 1,
									  1, A_NORMAL, 9, NULL);
						}
				}
		}
}
