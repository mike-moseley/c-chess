#pragma once
#include "pieces.h"

char *white_glyphs[6] = {"♙","♘","♗","♖","♕","♔"}; 
char *black_glyphs[6] = {"♟","♞","♝","♜","♛","♚"};
char piece_chars[6] = {'p','N','B','R','Q','K'};

piece_t **white_pieces = {};
piece_t **black_pieces = {};

piece_t *new_piece(piece_kind_t kind, chess_color_t color, vec2_t *position, vec2_t **moves){
	
}
