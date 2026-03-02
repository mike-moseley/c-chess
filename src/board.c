#pragma once
#include "board.h"
#include "pieces.h"
#include <stdlib.h>
#include <ncurses.h>

int BOARD_BG_WHITE = 5;
int BOARD_BG_BLACK = 4;
int LINE_COLOR = 8;

board_t *new_board(int height, int width) {
	int size = height * width;
	cell_t **cells = calloc(size, sizeof(cell_t *));
	int i;
	for (i = 0; i < size; i++) {
		cells[i] = calloc(1, sizeof(cell_t));
	}
	board_t *board = calloc(1, sizeof(board_t));
	board->cells = cells;
	board->height = height;
	board->width = width;
	return board;
}

void free_board(board_t *board) {
	cell_t  **cells = board->cells;
	int size = board->height * board->width;
	int i;
	for (i = 0; i < size; i++) {
		free(cells[i]);
	}
	free(cells);
	free(board);
}

int coord_to_index(int y, int x, board_t *board) {
	return x + y * board->height;
}

piece_t **create_pieces(board_t *board) {
	piece_t **pieces = calloc(board->width*2, sizeof(piece_t *));
	return pieces;
}

void init_white_pieces_classic(board_t *board, piece_t *pieces[16]) {
	// Initialize pawns
	int i;
	for (i=0; i<board->width; i++) {
		piece_t *pawn = new_piece(PAWN,WHITE,1,i,pawn_white_moves);
		pieces[i] = pawn;
	}
	// Initialize knights
	piece_t *knight = new_piece(KNIGHT, WHITE, 0, 2, knight_moves);
	pieces[8] = knight;
	piece_t *knight_2 = new_piece(KNIGHT, WHITE, 0, 4, knight_moves);
	pieces[9] = knight_2;
}
void draw_board(WINDOW *window, board_t *board) {
	// Draw outer borders
	// TODO: replace with border when board window is implemented
	// wborder(window, 0, 0, 0, 0, 0, 0, 0, 0);
	attron(COLOR_PAIR(3));
	mvwhline(window,0,0,ACS_HLINE,board->width*2);
	mvwhline(window,board->height*2,1,ACS_HLINE,board->width*2);
	mvwvline(window,1,0,ACS_VLINE,board->height*2);
	mvwvline(window,1,board->width*2,ACS_VLINE,board->height*2);

	mvwaddch(window,0,0,ACS_ULCORNER);
	mvwaddch(window,0,board->width*2,ACS_URCORNER);
	mvwaddch(window,board->height*2,0,ACS_LLCORNER);
	mvwaddch(window,board->height*2,board->width*2,ACS_LRCORNER);
	attroff(COLOR_PAIR(3));

	int y,x;
	
	for(y=0; y<=board->height*2; y++) {
		for(x=0; x<=board->width*2; x++) {
			// Cells where lines meet top edge
			attron(COLOR_PAIR(3));
			if((y == 0) && (x%2 == 0) && (x != 0) && (x!=board->width*2)) {
				mvwaddch(window, y, x, ACS_TTEE);
			}
			// Cells where lines meet bottom edge
			if((y == board->height*2) && (x%2  == 0) && (x != 0) && (x!=board->width*2)) {
				mvwaddch(window, y, x, ACS_BTEE);
			}
			if((x == 0) && (y%2 == 0) && (y!=0) && (y!=board->height*2)) {
				mvwaddch(window, y, x, ACS_LTEE);
			}
			if((x == board->width*2) && (y%2 == 0) && (y!=0) && (y!=board->height*2)) {
				mvwaddch(window, y, x, ACS_RTEE);
			}

			if ((y != 0) && (x!=0) && (y!=board->height*2) && (x!=board->width*2)){
				// Cells where lines cross
				if((x%2 == 0) && (y%2 == 0)){
					mvwaddch(window,y,x,ACS_PLUS);
				}
				// Vertical lines
				if(y%2 == 1){
					mvwaddch(window,y,x,ACS_VLINE);
				}
				// Horizontal lines
				if(x%2 == 1){
					mvwaddch(window,y,x,ACS_HLINE);
				}
				attroff(COLOR_PAIR(3));
				// Every space
				if((x%2 == 1)&&(y%2 == 1)){
					mvwaddch(window,y,x, ' ');
				}
				// Color spaces
				// TODO: When pieces are implemented if there is a piece on x//2,y//2
				// put piece from board->elements[x//2,y//2]?
				int coord_idx = coord_to_index(y/2, x/2, board);
				if(((x%4 == 3) && (y%4 == 1)) || ((x%4 == 1) && (y%4 ==3))){
					if ( board->cells[coord_idx] != NULL ){
						// attron(COLOR_PAIR(4));
						// mvwprintw(window, 16-1, 7, "%s",white_glyphs[5]);
						// attroff(COLOR_PAIR(4));
						mvwchgat(window,y,x, 4, A_NORMAL, 1, NULL);
					} else {
						mvwchgat(window,y,x, 1, A_NORMAL, 1, NULL);
					}
				}
				if(((x%4 == 3) && (y%4 == 3))||((x%4 == 1)&& (y%4 == 1))){
					if ( board->cells[coord_idx] != NULL ){
						// attron(COLOR_PAIR(5));
						// mvwprintw(window, 16-1, 7, "%s",white_glyphs[5]);
						// attroff(COLOR_PAIR(5));
					} else {
						mvwchgat(window,y,x, 1, A_NORMAL, 2, NULL);
					}
				}
			}
		}
	}
}
