#pragma once

typedef struct Vec2 {
	int y;
	int x;
} vec2_t;

extern vec2_t pawn_white_moves[3];
extern vec2_t pawn_black_moves[3];
extern vec2_t knight_moves[8];
extern vec2_t bishop_moves[4];
extern vec2_t rook_moves[4];
extern vec2_t king_queen_moves[8];
