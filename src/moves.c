#include "moves.h"
#include "board.h"
#include "pieces.h"
#include <ncurses.h>
#include <stdlib.h>
#include <limits.h>

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

vec2_t get_closest_move_up(struct Piece *piece, int y, int x) {
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t *move = calloc(1, sizeof(vec2_t));
	vec2_t *closest_vec = calloc(1, sizeof(vec2_t));
	vec2_t *def = calloc(1, sizeof(vec2_t));

	int i;
	for(i=0; i<piece->moves_count; i++){
		*move = piece->moves[i];
		if (move->y < y) {
			int dist_y = move->y - y;
			/*
			// abs because we don't care about direction here
			*/
			int abs_dist_x = abs(move->x - x); 
			
			if ((dist_y < closest) || ((dist_y == closest) && abs_dist_x < second_closest)) {
				closest = dist_y;
				second_closest = abs_dist_x;
				closest_idx = i;
			}
		}
	}
	if (closest_idx != -1) {
		closest_vec->y = piece->moves[closest_idx].y;
		closest_vec->x= piece->moves[closest_idx].x;
		return *closest_vec;
	}
	def->y = y;
	def->x = x;
	return *def;
}

vec2_t get_closest_move_down(struct Piece *piece, int y, int x) {
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t *move = calloc(1, sizeof(vec2_t));
	vec2_t *closest_vec = calloc(1, sizeof(vec2_t));
	vec2_t *def = calloc(1, sizeof(vec2_t));

	int i;
	for(i=0; i<piece->moves_count; i++){
		*move = piece->moves[i];
		if (move->y > y) {
			int dist_y = move->y - y;
			int abs_dist_x = abs(move->x - x); 
			
			if ((dist_y < closest) || ((dist_y == closest) && abs_dist_x < second_closest)) {
				closest = dist_y;
				second_closest = abs_dist_x;
				closest_idx = i;
			}
		}
	}
	if (closest_idx != -1) {
		closest_vec->y = piece->moves[closest_idx].y;
		closest_vec->x = piece->moves[closest_idx].x;
		return *closest_vec;
	}
	def->y = y;
	def->x = x;
	return *def;
}

vec2_t get_closest_move_left(struct Piece *piece, int y, int x) {
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t *move = calloc(1, sizeof(vec2_t));
	vec2_t *closest_vec = calloc(1, sizeof(vec2_t));
	vec2_t *def = calloc(1, sizeof(vec2_t));

	int i;
	for(i=0; i<piece->moves_count; i++){
		move = &piece->moves[i];
		if (move->x < x) {
			int dist_x = move->x - x;
			int abs_dist_y = abs(move->y - y); 
			
			if ((dist_x < closest) || ((dist_x == closest) && abs_dist_y < second_closest)) {
				closest = dist_x;
				second_closest = abs_dist_y;
				closest_idx = i;
			}
		}
	}
	if (closest_idx != -1) {
		closest_vec->y = piece->moves[closest_idx].y;
		closest_vec->x = piece->moves[closest_idx].x;
		return *closest_vec;
	}
	def->y = y;
	def->x = x;
	return *def;
}

vec2_t get_closest_move_right(struct Piece *piece, int y, int x) {
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t *move = calloc(1, sizeof(vec2_t));
	vec2_t *closest_vec = calloc(1, sizeof(vec2_t));
	vec2_t *def = calloc(1, sizeof(vec2_t));

	int i;
	for(i=0; i<piece->moves_count; i++){
		move = &piece->moves[i];
		if (move->x > x) {
			int dist_x = move->x - x;
			int abs_dist_y = abs(move->y - y); 
			
			if ((dist_x < closest) || ((dist_x == closest) && abs_dist_y < second_closest)) {
				closest = dist_x;
				second_closest = abs_dist_y;
				closest_idx = i;
			}
		}
	}
	if (closest_idx != -1) {
		closest_vec-> y = piece->moves[closest_idx].y;
		closest_vec->x = piece->moves[closest_idx].x;
		return *closest_vec;
	}
	def->y = y;
	def->x = x;
	return *def;
}

void compute_moves(struct Board *board, struct Piece *piece) {
	/*
	// 28 maximum number of moves
	*/ 
	vec2_t *result = calloc(28, sizeof(vec2_t));
	int i;
	piece->moves_count = 0;

	switch(piece->kind) {
		case PAWN:
		/* TODO: */
		break;
		case KING: {
			int y;
			int x;
			for (i = 0; i < 8; i++) {
				y = piece->y + king_queen_moves[i].y;
				x = piece->x + king_queen_moves[i].x;
				if (check_bounds(board, y, x)){
					int idx = coord_to_index(board, y, x);
					piece_t *dest = board->cells[idx]->piece;
					if ((dest == NULL) || (dest->color != piece->color)) {
						result[piece->moves_count].y = y;
						result[piece->moves_count].x = x;
						piece->moves_count++;
						board->cells[idx]->moveable = 1;
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
					piece_t *dest = board->cells[idx]->piece;
					if ((dest == NULL) || (dest->color != piece->color)) {
						result[piece->moves_count].y = y;
						result[piece->moves_count].x = x;
						piece->moves_count++;
						board->cells[idx]->moveable = 1;
					}
				}
			}
			break;
		}
		case BISHOP:
		/* TODO:*/
		case ROOK:
		/* TODO:*/
		case QUEEN:
		/* TODO:*/
		default:
			break;
	}	
	piece->moves = result;
}

