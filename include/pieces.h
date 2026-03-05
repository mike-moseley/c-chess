#pragma once
#include "moves.h"

typedef enum chess_color
{
	WHITE,
	BLACK
} chess_color_t;

/*
// Edit piece_chars in pieces.c if pieces are added
*/
typedef enum piece_kind
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
} piece_kind_t;
extern char piece_chars[6];

struct Board;
typedef struct Piece
{
	piece_kind_t kind;
	chess_color_t color;
	char symbol;
	int y;
	int x;
	vec2_t *moves;
	int moves_count;
} piece_t;

piece_t *new_piece (piece_kind_t kind, chess_color_t color, int y, int x);
char *piece_to_string (piece_t *piece);
char *piece_arr_to_string (piece_t **piece, int count);
void init_white_pieces_classic (struct Board *board, piece_t **pieces);
void init_black_pieces_classic (struct Board *board, piece_t **pieces);
piece_t **create_pieces (struct Board *board);
void free_pieces (piece_t *piece);
