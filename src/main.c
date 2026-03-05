#include "board.h"
#include "moves.h"
#include "pieces.h"
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
	board_t *board;
	piece_t **white_pieces;
	piece_t **black_pieces;
	piece_t **white_captures;
	int white_capture_count;
	piece_t **black_captures;
	int black_capture_count;
	int cursor_y = 0;
	int cursor_x = 0;
	int tmp_y = 0;
	int tmp_x = 0;
	chess_color_t turn = WHITE;
	piece_t *selected = NULL;
	int ch;

	setlocale (LC_ALL, "");
	initscr ();
	noecho ();
	cbreak ();
	start_color ();
	use_default_colors ();
	curs_set (0);
	keypad (stdscr, TRUE);
	ESCDELAY = 10;

	if (has_colors () == FALSE)
		{
			endwin ();
			printf ("Your terminal doesn't support colors.");
			return 1;
		}

	if (COLORS < 16)
		{
			endwin ();
			printf ("Your terminal doesn't support at least 16 colors.");
			return 1;
		}

	/*
	// White space
	// Black space
	// Border line
	// White on white space
	// White on black space
	// Black on white space
	// Black on black space
	// Selected space
	// Available move
	*/
	init_pair (1, -1, BOARD_BG_WHITE);
	init_pair (2, -1, BOARD_BG_BLACK);
	init_pair (3, LINE_COLOR, -1);
	init_pair (4, WHITE_COLOR, BOARD_BG_WHITE);
	init_pair (5, WHITE_COLOR, BOARD_BG_BLACK);
	init_pair (6, BLACK_COLOR, BOARD_BG_WHITE);
	init_pair (7, BLACK_COLOR, BOARD_BG_BLACK);
	init_pair (8, 0, 14);
	init_pair (9, 0, 2);

	/*
	// TODO: Make window for board and pass to draw_board
	*/

	board = new_board (8, 8);
	white_pieces = create_pieces (board);
	init_white_pieces_classic (board, white_pieces);
	black_pieces = create_pieces (board);
	init_black_pieces_classic (board, black_pieces);
	white_captures = create_pieces (board);
	white_capture_count = 0;
	black_captures = create_pieces (board);
	black_capture_count = 0;
	add_pieces_to_cells (board, white_pieces);
	add_pieces_to_cells (board, black_pieces);

	/*
	// TODO: Now just defining selection by moving cursor.
	// Add select by typing square name (e4) in future.
	// Make it so moving the cursor after selecting a piece only cycles
	// over moveable
	*/
	refresh ();
	while ((ch = getch ()) != 'q')
		{
			if (turn == WHITE)
				{
					mvwprintw (stdscr, 18, 0, "Turn: White");
				}
			else
				{
					mvwprintw (stdscr, 0, 0, "Turn: Black");
				}
			switch (ch)
				{
				case KEY_UP:
				case 'k':
					tmp_y = cursor_y - 1;
					if (check_bounds (board, tmp_y, cursor_x))
						{
							if (selected != NULL)
								{
									/*
									// TODO: Replace with distance function
									inside get_closest_move... fns
									// to get better movement?
									*/
									vec2_t closest = get_closest_move_up (
										selected, cursor_y, cursor_x);
									cursor_x = closest.x;
									cursor_y = closest.y;
								}
							else
								{
									cursor_y = tmp_y;
								}
						}
					break;
				case KEY_DOWN:
				case 'j':
					tmp_y = cursor_y + 1;
					if (check_bounds (board, tmp_y, cursor_x))
						{
							if (selected != NULL)
								{
									vec2_t closest = get_closest_move_down (
										selected, cursor_y, cursor_x);
									cursor_x = closest.x;
									cursor_y = closest.y;
								}
							else
								{
									cursor_y = tmp_y;
								}
						}
					break;
				case KEY_LEFT:
				case 'h':
					tmp_x = cursor_x - 1;
					if (check_bounds (board, cursor_y, tmp_x))
						{
							if (selected != NULL)
								{
									vec2_t closest = get_closest_move_left (
										selected, cursor_y, cursor_x);
									cursor_x = closest.x;
									cursor_y = closest.y;
								}
							else
								{
									cursor_x = tmp_x;
								}
						}
					break;
				case KEY_RIGHT:
				case 'l':
					tmp_x = cursor_x + 1;
					if (check_bounds (board, cursor_y, tmp_x))
						{
							if (selected != NULL)
								{
									vec2_t closest = get_closest_move_right (
										selected, cursor_y, cursor_x);
									cursor_x = closest.x;
									cursor_y = closest.y;
								}
							else
								{
									cursor_x = tmp_x;
								}
						}
					break;

				case '\n':
					{
						int idx = coord_to_index (board, cursor_y, cursor_x);
						if (selected == NULL)
							{
								piece_t *candidate = board->cells[idx]->piece;
								if (candidate != NULL
									&& candidate->color == turn)
									{
										selected = candidate;
										compute_moves (board, selected);
									}
							}
						else
							{
								if (board->cells[idx]->moveable == 1)
									{
										int selected_y = selected->y;
										int selected_x = selected->x;
										int selected_idx = coord_to_index (
											board, selected_y, selected_x);
										/*
										// TODO: Implement capture if
										board->cells[idx]->piece != NULL
										// if (board->cells[idx]->piece !=
										NULL){
										// }
										*/
										if (board->cells[idx]->piece != NULL)
											{
												if (board->cells[idx]
														->piece->color
													!= WHITE)
													{
														white_captures
															[white_capture_count]
															= board->cells[idx]
																  ->piece;
														white_capture_count++;
													}
												else
													{
														black_captures
															[black_capture_count]
															= board->cells[idx]
																  ->piece;
														black_capture_count++;
													}
											}
										board->cells[idx]->piece = selected;
										board->cells[idx]->piece->y = cursor_y;
										board->cells[idx]->piece->x = cursor_x;
										board->cells[selected_idx]->piece
											= NULL;
										selected = NULL;
										clear_board_moveable (board);
										if (turn == WHITE)
											{
												turn = BLACK;
											}
										else
											{
												turn = WHITE;
											}
									}
							}
						break;
					}
				case 27:
					selected = NULL;
					clear_board_moveable (board);
					break;
				}

			draw_board (stdscr, board, cursor_y, cursor_x, selected);

			mvwprintw (
				stdscr, 19, 0, "White Captures: %s",
				piece_arr_to_string (white_captures, white_capture_count));
			mvwprintw (
				stdscr, 20, 0, "Black Captures: %s",
				piece_arr_to_string (black_captures, black_capture_count));
			mvwprintw (stdscr, 22, 0, "Selected: %s     ",
					   piece_to_string (selected));
			refresh ();
		}
	endwin ();

	free_board (board);

	return 0;
}
