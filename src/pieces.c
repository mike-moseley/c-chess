#include "pieces.h"
#include "board.h"
#include <stdlib.h>

char piece_chars[6] = { 'p', 'N', 'B', 'R', 'Q', 'K' };

piece_t *
new_piece (piece_kind_t kind, chess_color_t color, int y, int x)
{
	piece_t *piece = calloc (1, sizeof (piece_t));
	piece->kind = kind;
	piece->color = color;
	piece->y = y;
	piece->x = x;
	piece->moves = NULL;
	piece->moves_count = 0;
	piece->symbol = piece_chars[kind];

	return piece;
}

void
free_piece (board_t *board, piece_t **pieces)
{
	int i;
	for (i = 0; i < board->width * 2; i++)
	{
		free (pieces[i]);
	}
	free (pieces);
}

piece_t **
create_pieces (board_t *board)
{
	piece_t **pieces = calloc (board->width * 2, sizeof (piece_t *));
	return pieces;
}

char *
piece_to_string (piece_t *piece)
{
	char *piece_string;
	if (piece != NULL)
	{
		switch (piece->color)
		{
		case WHITE:
			switch (piece->kind)
			{
			case PAWN:
				piece_string = "White Pawn";
				break;
			case KNIGHT:
				piece_string = "White Knight";
				break;
			case BISHOP:
				piece_string = "White Bishop";
				break;
			case ROOK:
				piece_string = "White Rook";
				break;
			case QUEEN:
				piece_string = "White Queen";
				break;
			case KING:
				piece_string = "White King";
				break;
			}
			break;
		case BLACK:
			switch (piece->kind)
			{
			case PAWN:
				piece_string = "Black Pawn";
				break;
			case KNIGHT:
				piece_string = "Black Knight";
				break;
			case BISHOP:
				piece_string = "Black Bishop";
				break;
			case ROOK:
				piece_string = "Black Rook";
				break;
			case QUEEN:
				piece_string = "Black Queen";
				break;
			case KING:
				piece_string = "Black King";
				break;
				break;
			}
		}
	}
	else
	{
		piece_string = "             ";
	}
	return piece_string;
}
char *
piece_arr_to_string (piece_t **pieces, int count)
{
	char *str = calloc (count + 1, sizeof (char));
	int i;
	for (i = 0; i < count; i++)
	{
		str[i] = pieces[i]->symbol;
	}
	str[i++] = '\0';
	return str;
}

void
init_white_pieces_classic (board_t *board, piece_t **pieces)
{
	/*
	// Initialize pawns
	*/
	int i;
	for (i = 0; i < board->width; i++)
	{
		piece_t *pawn = new_piece (PAWN, WHITE, 6, i);
		pieces[i] = pawn;
	}
	/*
	// Initialize knights
	*/
	pieces[8] = new_piece (KNIGHT, WHITE, 7, 2);
	pieces[9] = new_piece (KNIGHT, WHITE, 7, 5);
	/*
	// Initialize bishops
	*/
	pieces[10] = new_piece (BISHOP, WHITE, 7, 1);
	pieces[11] = new_piece (BISHOP, WHITE, 7, 6);
	pieces[12] = new_piece (ROOK, WHITE, 7, 0);
	pieces[13] = new_piece (ROOK, WHITE, 7, 7);
	pieces[14] = new_piece (KING, WHITE, 7, 4);
	pieces[15] = new_piece (QUEEN, WHITE, 7, 3);
}

void
init_black_pieces_classic (board_t *board, piece_t **pieces)
{
	/*
	// Initialize pawns
	*/
	int i;
	for (i = 0; i < board->width; i++)
	{
		pieces[i] = new_piece (PAWN, BLACK, 1, i);
	}
	/*
	// Initialize knights
	*/
	pieces[8] = new_piece (KNIGHT, BLACK, 0, 2);
	pieces[9] = new_piece (KNIGHT, BLACK, 0, 5);
	/*
	// Initialize bishops
	*/
	pieces[10] = new_piece (BISHOP, BLACK, 0, 1);
	pieces[11] = new_piece (BISHOP, BLACK, 0, 6);
	pieces[12] = new_piece (ROOK, BLACK, 0, 0);
	pieces[13] = new_piece (ROOK, BLACK, 0, 7);
	pieces[14] = new_piece (KING, BLACK, 0, 4);
	pieces[15] = new_piece (QUEEN, BLACK, 0, 3);
}
