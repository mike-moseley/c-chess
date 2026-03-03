#include "pieces.h"
#include "board.h"
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	start_color();
	use_default_colors();
	curs_set(0);
	keypad(stdscr, TRUE);
	ESCDELAY = 10;

	if(has_colors()==FALSE){
		endwin();
		printf("Your terminal doesn't support colors.");
		return 1;
	}

	if(COLORS < 16) {
		endwin();
		printf("Your terminal doesn't support at least 16 colors.");
		return 1;
	}

	init_pair(1,-1, BOARD_BG_WHITE);				// White space
	init_pair(2,-1, BOARD_BG_BLACK);				// Black space
	init_pair(3, LINE_COLOR, -1);					// Border lines
	init_pair(4, WHITE_COLOR, BOARD_BG_WHITE);		// White on white space
	init_pair(5, WHITE_COLOR, BOARD_BG_BLACK);		// White on black space
	init_pair(6, BLACK_COLOR, BOARD_BG_WHITE);		// Black on white space
	init_pair(7, BLACK_COLOR, BOARD_BG_BLACK);		// Black on black space
	init_pair(8, 0, 14);							// Selected space
	init_pair(9, 0, 2);								// Available move

	// TODO: Make window for board and pass to draw_board
	board_t *board = new_board(8,8);
	piece_t **white_pieces = create_pieces(board);
	init_white_pieces_classic(board, white_pieces);
	piece_t **black_pieces = create_pieces(board);
	init_black_pieces_classic(board, black_pieces);
	piece_t **white_captures = create_pieces(board);
	piece_t **black_captures = create_pieces(board);
	add_pieces_to_cells(board, white_pieces);
	add_pieces_to_cells(board, black_pieces);
	
	int cursor_y = 0;
	int cursor_x = 0;
	int tmp_y = 0;
	int tmp_x = 0;

	piece_t *selected = NULL;

	// TODO: Now just defining selection by moving cursor.
	// Add select by typing square name (e4) in future.
	refresh();
	int ch;
	while ((ch = getch()) != 'q') {
		switch (ch) {
			case KEY_UP:
			case 'k':
				tmp_y = cursor_y - 1;
				if (check_bounds(board, tmp_y, cursor_x)) {
					cursor_y = tmp_y;
				}
				break;
			case KEY_DOWN:
			case 'j':
				tmp_y = cursor_y + 1;
				if (check_bounds(board, tmp_y, cursor_x)) {
					cursor_y = tmp_y;
				}
				break;
			case KEY_LEFT:
			case 'h':
				tmp_x = cursor_x - 1;
				if (check_bounds(board, cursor_y, tmp_x)) {
					cursor_x = tmp_x;
				}
				break;
			case KEY_RIGHT:
			case 'l':
				tmp_x = cursor_x + 1;
				if (check_bounds(board, cursor_y, tmp_x)) {
					cursor_x = tmp_x;
				}
				break;
			case '\n':{
				int idx = coord_to_index(board, cursor_y, cursor_x);
				if (selected == NULL){
					selected = board->cells[idx]->piece;
					if (selected != NULL) {
						compute_moves(board,selected);
					}
				} else {
					if (board->cells[idx]->moveable == 1) {
						int selected_y = selected->y;
						int selected_x = selected->x;
						int selected_idx = coord_to_index(board, selected_y, selected_x);
						// TODO: Implement capture if board->cells[idx]->piece != NULL
						board->cells[idx]->piece = selected;
						board->cells[idx]->piece->y = cursor_y;
						board->cells[idx]->piece->x = cursor_x;
						board->cells[selected_idx]->piece = NULL;
						selected = NULL;
						clear_board_moveable(board);
					}
				}
				break;
			}
			case 27:
				selected = NULL;
				clear_board_moveable(board);
				break;
		}
		draw_board(stdscr, board, cursor_y, cursor_x, selected);

		mvwprintw(stdscr, 18, 0, "Selected: %s     ", piece_to_string(selected));
		refresh();
	}
	endwin();

	free_board(board);
	
	return 0;
}
