#include "moves.h"

vec2_t pawn_white_moves[3] = {{1,0},{1,-1},{1,1}};
vec2_t pawn_black_moves[3] = {{-1,0},{-1,-1},{-1,1}};
vec2_t knight_moves[8] = {
	{2,1}  , {1,2},
	{-2,1} , {1,-2},
	{2,-1} , {-1,2},
	{-2,-1}, {-1,-2}
};
