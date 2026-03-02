#include "pieces.h"
#include <stdlib.h>

char piece_chars[6] = {'p','N','B','R','Q','K'};

piece_t **white_pieces = NULL;
piece_t **black_pieces = NULL;

piece_t *new_piece(piece_kind_t kind, chess_color_t color, int y, int x, vec2_t **moves) {
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


