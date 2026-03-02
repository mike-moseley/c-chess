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

	init_pair(1,-1, BOARD_BG_WHITE);
	init_pair(2,-1, BOARD_BG_BLACK);
	init_pair(3, LINE_COLOR, -1);
	init_pair(4, WHITE_COLOR, BOARD_BG_WHITE);
	init_pair(5, WHITE_COLOR, BOARD_BG_BLACK);
	init_pair(6, BLACK_COLOR, BOARD_BG_WHITE);
	init_pair(7, BLACK_COLOR, BOARD_BG_BLACK);

	// TODO: Make window for board and pass to draw_board
	board_t *board = new_board(8,8);
	piece_t **white_pieces = create_pieces(board);
	init_white_pieces_classic(board, white_pieces);
	piece_t **black_pieces = create_pieces(board);
	init_black_pieces_classic(board, black_pieces);
	add_pieces_to_cells(board, white_pieces);
	add_pieces_to_cells(board, black_pieces);
	draw_board(stdscr, board);
	
	refresh();
	getch();
	endwin();

	free_board(board);
	return 0;
}
