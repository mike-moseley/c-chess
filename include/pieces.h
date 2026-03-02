#pragma once

typedef enum chess_color {WHITE, BLACK} chess_color_t;

// Edit piece_chars in pieces.c if pieces are added
typedef enum piece_kind {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} piece_kind_t;
extern char piece_chars[6];

typedef struct Vec2 {
	int y;
	int x;
} vec2_t;

typedef struct Piece {
	piece_kind_t kind;
	chess_color_t color;
	char symbol;
	int y;
	int x;
	vec2_t **moves;
} piece_t;

extern piece_t **white_pieces;
extern piece_t **black_pieces;

piece_t *new_piece(piece_kind_t kind, chess_color_t color, int y, int x, vec2_t **moves);
