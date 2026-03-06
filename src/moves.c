#include "moves.h"
#include "board.h"
#include "pieces.h"
#include <limits.h>
#include <ncurses.h>
#include <stdlib.h>

vec2_t pawn_white_move[1] = { { -1, 0 } };
vec2_t pawn_white_double_move[1] = { { -2, 0 } };
vec2_t pawn_white_captures[3] = { { -1, -1 }, { -1, 1 } };
vec2_t pawn_black_move[1] = { { 1, 0 } };
vec2_t pawn_black_double_move[1] = { { 2, 0 } };
vec2_t pawn_black_captures[3] = { { 1, -1 }, { 1, 1 } };
vec2_t knight_moves[8] = { { 2, 1 },  { 1, 2 },	 { -2, 1 },	 { 1, -2 },
						   { 2, -1 }, { -1, 2 }, { -2, -1 }, { -1, -2 } };
vec2_t bishop_moves[4] = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };
vec2_t rook_moves[4] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
vec2_t king_queen_moves[8] = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 },
							   { 1, 0 }, { 0, 1 },	 { -1, 0 }, { 0, -1 } };

vec2_t
get_closest_move_up (struct Piece *piece, int y, int x)
{
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t move;
	vec2_t closest_vec;
	vec2_t def;

	int i;
	for (i = 0; i < piece->moves_count; i++)
		{
			move = piece->moves[i];
			if (move.y < y)
				{
					int dist_y = move.y - y;
					/*
					// abs because we don't care about direction here
					*/
					int abs_dist_x = abs (move.x - x);

					if ((dist_y < closest)
						|| ((dist_y == closest)
							&& abs_dist_x < second_closest))
						{
							closest = dist_y;
							second_closest = abs_dist_x;
							closest_idx = i;
						}
				}
		}
	if (closest_idx != -1)
		{
			closest_vec.y = piece->moves[closest_idx].y;
			closest_vec.x = piece->moves[closest_idx].x;
			return closest_vec;
		}
	def.y = y;
	def.x = x;
	return def;
}

vec2_t
get_closest_move_down (struct Piece *piece, int y, int x)
{
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t move;
	vec2_t closest_vec;
	vec2_t def;

	int i;
	for (i = 0; i < piece->moves_count; i++)
		{
			move = piece->moves[i];
			if (move.y > y)
				{
					int dist_y = move.y - y;
					int abs_dist_x = abs (move.x - x);

					if ((dist_y < closest)
						|| ((dist_y == closest)
							&& abs_dist_x < second_closest))
						{
							closest = dist_y;
							second_closest = abs_dist_x;
							closest_idx = i;
						}
				}
		}
	if (closest_idx != -1)
		{
			closest_vec.y = piece->moves[closest_idx].y;
			closest_vec.x = piece->moves[closest_idx].x;
			return closest_vec;
		}
	def.y = y;
	def.x = x;
	return def;
}

vec2_t
get_closest_move_left (struct Piece *piece, int y, int x)
{
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t move;
	vec2_t closest_vec;
	vec2_t def;

	int i;
	for (i = 0; i < piece->moves_count; i++)
		{
			move = piece->moves[i];
			if (move.x < x)
				{
					int dist_x = move.x - x;
					int abs_dist_y = abs (move.y - y);

					if ((dist_x < closest)
						|| ((dist_x == closest)
							&& abs_dist_y < second_closest))
						{
							closest = dist_x;
							second_closest = abs_dist_y;
							closest_idx = i;
						}
				}
		}
	if (closest_idx != -1)
		{
			closest_vec.y = piece->moves[closest_idx].y;
			closest_vec.x = piece->moves[closest_idx].x;
			return closest_vec;
		}
	def.y = y;
	def.x = x;
	return def;
}

vec2_t
get_closest_move_right (struct Piece *piece, int y, int x)
{
	int closest_idx = -1;
	int closest = INT_MAX;
	int second_closest = INT_MAX;
	vec2_t move;
	vec2_t closest_vec;
	vec2_t def;

	int i;
	for (i = 0; i < piece->moves_count; i++)
		{
			move = piece->moves[i];
			if (move.x > x)
				{
					int dist_x = move.x - x;
					int abs_dist_y = abs (move.y - y);

					if ((dist_x < closest)
						|| ((dist_x == closest)
							&& abs_dist_y < second_closest))
						{
							closest = dist_x;
							second_closest = abs_dist_y;
							closest_idx = i;
						}
				}
		}
	if (closest_idx != -1)
		{
			closest_vec.y = piece->moves[closest_idx].y;
			closest_vec.x = piece->moves[closest_idx].x;
			return closest_vec;
		}
	def.y = y;
	def.x = x;
	return def;
}

void
compute_moves (struct Board *board, struct Piece *piece)
{
	vec2_t *result;
	/* If this was called before on the same piece
	 * we must free the run's moves or we leak it*/
	free (piece->moves);

	/*
	// 28 maximum number of moves
	*/
	result = calloc (28, sizeof (vec2_t));
	piece->moves_count = 0;

	switch (piece->kind)
		{
		case PAWN:
			{
				int i;
				int y;
				int x;
				int idx;

				idx = coord_to_index (board, piece->y, piece->x);
				if (piece->color == WHITE)
					{
						/* Starting row logic */
						vec2_t move1;
						vec2_t move2;
						int move1_idx = 0;
						int move2_idx = 0;
						cell_t *move_1_cell;
						cell_t *move_2_cell;
						move1.y = piece->y - 1;
						move1.x = piece->x;
						move_1_cell = board->cells[move1_idx];
						move2.y = piece->y - 2;
						move2.x = piece->x;
						move_2_cell = board->cells[move2_idx];
						{
							if (check_bounds (board, move1.y, move1.x)
								&& move_1_cell->piece == NULL)
								{
									move1_idx = coord_to_index (board, move1.y,
																move1.x);
									result[piece->moves_count] = move1;
									piece->moves_count++;
									board->cells[move1_idx]->moveable = 1;

									if (piece->y == 6)
										{
											if (check_bounds (board, move2.y,
															  move2.x)
												&& move_2_cell->piece == NULL)
												{
													move2_idx
														= coord_to_index (
															board, move2.y,
															move2.x);
													board->cells[move2_idx]
														->moveable
														= 1;
													result[piece->moves_count]
														= move2;
													piece->moves_count++;
												}
										}
								}
						}
					}
				if (piece->color == BLACK)
					{
					}

				break;
			}
		case KING:
			{
				int i;
				int y;
				int x;
				for (i = 0; i < 8; i++)
					{
						y = piece->y + king_queen_moves[i].y;
						x = piece->x + king_queen_moves[i].x;
						if (check_bounds (board, y, x))
							{
								int idx = coord_to_index (board, y, x);
								piece_t *dest = board->cells[idx]->piece;
								if ((dest == NULL)
									|| (dest->color != piece->color))
									{
										result[piece->moves_count].y = y;
										result[piece->moves_count].x = x;
										piece->moves_count++;
										board->cells[idx]->moveable = 1;
									}
							}
					}
			}
			break;
		case KNIGHT:
			{
				int i;
				int y;
				int x;
				for (i = 0; i < 8; i++)
					{
						y = piece->y + knight_moves[i].y;
						x = piece->x + knight_moves[i].x;
						if (check_bounds (board, y, x))
							{
								int idx = coord_to_index (board, y, x);
								piece_t *dest = board->cells[idx]->piece;
								if ((dest == NULL)
									|| (dest->color != piece->color))
									{
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
			{
				int y;
				int x;
				int i;
				int idx;
				int count;
				piece_t *dest;
				for (i = 0; i < 4; i++)
					{
						for (count = 1; count < 8; count++)
							{
								y = piece->y + bishop_moves[i].y * count;
								x = piece->x + bishop_moves[i].x * count;
								if (!check_bounds (board, y, x))
									break;
								idx = coord_to_index (board, y, x);
								dest = board->cells[idx]->piece;

								/* Blocked by same color */
								if (dest != NULL
									&& dest->color == piece->color)
									break;
								result[piece->moves_count].y = y;
								result[piece->moves_count].x = x;
								piece->moves_count++;
								board->cells[idx]->moveable = 1;

								/* Capture */
								if (dest != NULL)
									break;
							}
					}
				break;
			}
		case ROOK:
			{

				int y;
				int x;
				int i;
				int idx;
				int count;
				piece_t *dest;
				for (i = 0; i < 4; i++)
					{
						for (count = 1; count < 8; count++)
							{
								y = piece->y + rook_moves[i].y * count;
								x = piece->x + rook_moves[i].x * count;
								if (!check_bounds (board, y, x))
									break;
								idx = coord_to_index (board, y, x);
								dest = board->cells[idx]->piece;

								/* Blocked by same color */
								if (dest != NULL
									&& dest->color == piece->color)
									break;
								result[piece->moves_count].y = y;
								result[piece->moves_count].x = x;
								piece->moves_count++;
								board->cells[idx]->moveable = 1;

								/* Capture */
								if (dest != NULL)
									break;
							}
					}
				break;
			}
		case QUEEN:
			{
				int y;
				int x;
				int i;
				int idx;
				int count;
				piece_t *dest;
				for (i = 0; i < 8; i++)
					{
						for (count = 1; count < 8; count++)
							{
								y = piece->y + king_queen_moves[i].y * count;
								x = piece->x + king_queen_moves[i].x * count;
								if (!check_bounds (board, y, x))
									break;
								idx = coord_to_index (board, y, x);
								dest = board->cells[idx]->piece;

								/* Blocked by same color */
								if (dest != NULL
									&& dest->color == piece->color)
									break;
								result[piece->moves_count].y = y;
								result[piece->moves_count].x = x;
								piece->moves_count++;
								board->cells[idx]->moveable = 1;

								/* Capture */
								if (dest != NULL)
									break;
							}
					}
				break;
			}
		default:
			break;
		}
	piece->moves = result;
}
