#pragma once
#include "board.h"
#include "moves.h"
#include "pieces.h"
#include <stdlib.h>
#include <ncurses.h>

int BOARD_BG_WHITE = 5;
int BOARD_BG_BLACK = -1;
int WHITE_COLOR = 14;
int BLACK_COLOR = 4;
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

int coord_to_index(board_t *board, int y, int x) {
	return x + y * board->width;
}

piece_t **create_pieces(board_t *board) {
	piece_t **pieces = calloc(board->width*2, sizeof(piece_t *));
	return pieces;
}

void init_white_pieces_classic(board_t *board, piece_t *pieces[16]) {
	// Initialize pawns
	int i;
	for (i=0; i<board->width; i++) {
		piece_t *pawn = new_piece(PAWN,WHITE,6,i,pawn_white_moves);
		pieces[i] = pawn;
	}
	// Initialize knights
	piece_t *knight = new_piece(KNIGHT, WHITE, 7, 2, knight_moves);
	pieces[8] = knight;
	piece_t *knight_2 = new_piece(KNIGHT, WHITE, 7, 5, knight_moves);
	pieces[9] = knight_2;
	// Initialize bishops
	piece_t *bishop = new_piece(BISHOP, WHITE, 7, 1, bishop_moves);
	pieces[10] = bishop;
	piece_t *bishop_2 = new_piece(BISHOP, WHITE, 7, 6, bishop_moves);
	pieces[11] = bishop_2;
	piece_t *rook = new_piece(ROOK, WHITE, 7, 0, rook_moves);
	pieces[12] = rook;
	piece_t *rook_2 = new_piece(ROOK, WHITE, 7, 7, rook_moves);
	pieces[13] = rook_2;
	piece_t *king = new_piece(KING, WHITE, 7, 4, king_queen_moves);
	pieces[14] = king;
	piece_t *queen = new_piece(QUEEN, WHITE, 7, 3, king_queen_moves);
	pieces[15] = queen;
}
void init_black_pieces_classic(board_t *board, piece_t *pieces[16]) {
	// Initialize pawns
	int i;
	for (i=0; i<board->width; i++) {
		piece_t *pawn = new_piece(PAWN,BLACK,1,i,pawn_white_moves);
		pieces[i] = pawn;
	}
	// Initialize knights
	piece_t *knight = new_piece(KNIGHT, BLACK, 0, 2, knight_moves);
	pieces[8] = knight;
	piece_t *knight_2 = new_piece(KNIGHT, BLACK, 0, 5, knight_moves);
	pieces[9] = knight_2;
	// Initialize bishops
	piece_t *bishop = new_piece(BISHOP, BLACK, 0, 1, bishop_moves);
	pieces[10] = bishop;
	piece_t *bishop_2 = new_piece(BISHOP, BLACK, 0, 6, bishop_moves);
	pieces[11] = bishop_2;
	piece_t *rook = new_piece(ROOK, BLACK, 0, 0, rook_moves);
	pieces[12] = rook;
	piece_t *rook_2 = new_piece(ROOK, BLACK, 0, 7, rook_moves);
	pieces[13] = rook_2;
	piece_t *king = new_piece(KING, BLACK, 0, 4, king_queen_moves);
	pieces[14] = king;
	piece_t *queen = new_piece(QUEEN, BLACK, 0, 3, king_queen_moves);
	pieces[15] = queen;
}
void add_pieces_to_cells(board_t *board, piece_t *pieces[16]) {
	int i;
	for (i=0; i<16; i++){
		int piece_idx = coord_to_index(board, pieces[i]->y, pieces[i]->x);
		board->cells[piece_idx]->piece = pieces[i];
	}
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
			
			// Cells where lines meet edges
			attron(COLOR_PAIR(3));
			if((y == 0) && (x%2 == 0) && (x != 0) && (x!=board->width*2)) {
				mvwaddch(window, y, x, ACS_TTEE);
			}
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
				int current_idx = coord_to_index(board, y/2, x/2);
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

				piece_t *piece = board->cells[current_idx]->piece;
				if(((x%4 == 3) && (y%4 == 1)) || ((x%4 == 1) && (y%4 ==3))){
					if ((piece != NULL) && (piece->color == WHITE)){
						mvwaddch(window,y,x, piece->symbol | COLOR_PAIR(4)); 
					} else if ((piece != NULL) && (piece->color == BLACK)) {
						mvwaddch(window,y,x, piece->symbol | COLOR_PAIR(6)); 
					} else {
						mvwaddch(window,y,x, ' ' | COLOR_PAIR(1)); 
					}
				}
				if(((x%4 == 3) && (y%4 == 3))||((x%4 == 1)&& (y%4 == 1))){
					if ((piece != NULL) && (piece->color == WHITE)){
						mvwaddch(window,y,x, piece->symbol | COLOR_PAIR(5)); 
					} else if ((piece != NULL) && (piece->color == BLACK)) {
						mvwaddch(window,y,x, piece->symbol | COLOR_PAIR(7)); 
					} else {
						mvwaddch(window,y,x, ' ' | COLOR_PAIR(2)); 
					}
				}
			}
		}
	}
}
