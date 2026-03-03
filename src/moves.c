#include "moves.h"
#include "board.h"
#include "pieces.h"
#include <ncurses.h>
#include <stdlib.h>

vec2_t pawn_white_moves[3] = {{1,0},{1,-1},{1,1}};
vec2_t pawn_black_moves[3] = {{-1,0},{-1,-1},{-1,1}};
vec2_t knight_moves[8] = {
	{2,1}  , {1,2},
	{-2,1} , {1,-2},
	{2,-1} , {-1,2},
	{-2,-1}, {-1,-2}
};
vec2_t bishop_moves[4] = {
	{1,1}  ,{-1,-1},
	{1,-1} ,{-1,1}
};
vec2_t rook_moves[4] = {
	{1,0}  ,{0,1},
	{-1,0} ,{0,-1}
};
vec2_t king_queen_moves[8] = {
	{1,1}  ,{-1,-1},
	{1,-1} ,{-1,1},
	{1,0}  ,{0,1},
	{-1,0} ,{0,-1}
};

vec2_t *compute_moves(struct Board *board, struct Piece *piece, int *count) {
	// 28 maximum number of moves
	vec2_t *result = calloc(28, sizeof(vec2_t));
	int i;

	switch(piece->kind) {
		case PAWN:
		// TODO:
		break;
		case KING: {
			int y;
			int x;
			for (i = 0; i < 8; i++) {
				y = piece->y + king_queen_moves[i].y;
				x = piece->x + king_queen_moves[i].x;
				if (check_bounds(board, y, x)){
					int idx = coord_to_index(board, y, x);
					if ((board->cells[idx]->piece != NULL) || (board->cells[idx]->piece->color != piece->color)) {
						result[*count].y = y;
						result[*count].x = x;
						(*count)++;
					}
				}
			}
			break;
		}
		case KNIGHT: {
			int y;
			int x;
			for (i = 0; i < 8; i++) {
				y = piece->y + knight_moves[i].y;
				x = piece->x + knight_moves[i].x;
				if (check_bounds(board, y, x)){
					int idx = coord_to_index(board, y, x);
					if ((board->cells[idx]->piece != NULL) || (board->cells[idx]->piece->color != piece->color)) {
						result[*count].y = y;
						result[*count].x = x;
						(*count)++;
					}
				}
			}
			break;
		}
		case BISHOP:
		// TODO:
		case ROOK:
		// TODO:
		case QUEEN:
		// TODO:
		default:
			break;
	}	
	return result;
}

