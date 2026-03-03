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
