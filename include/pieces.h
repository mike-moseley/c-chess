#pragma once

typedef enum chess_color {WHITE, BLACK} chess_color_t;
typedef enum piece_kind {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} piece_kind_t;

extern char *white_glyphs[6];
extern char *black_glyphs[6];

typedef struct Vec2 {
	int x;
	int y;
} vec2_t;

typedef struct Piece {
	enum piece_kind kind;
	enum chess_color color;
	vec2_t *position;
	vec2_t **moves;
} piece_t;
