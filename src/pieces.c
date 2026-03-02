#include "pieces.h"
#include "board.h"
#include "moves.h"
#include <stdlib.h>

char piece_chars[6] = {'p','N','B','R','Q','K'};

piece_t *new_piece(piece_kind_t kind, chess_color_t color, int y, int x, vec2_t *moves) {
	piece_t *piece = calloc(1,sizeof(piece_t));
	piece->kind = kind;
	piece->color = color;
	piece->y = y;
	piece->x = x;
	piece->moves = moves;
	piece->symbol = piece_chars[kind];

	return piece;
}

void free_piece(piece_t *piece) {
	// Moves will exist as a defined array of possible moves
	// for each piece... Do not free
	free(piece);
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


