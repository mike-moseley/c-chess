#include "pieces.h"
#include "board.h"
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

void draw_board() {

}

int main() {
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	use_default_colors();

	if(has_colors()==FALSE){
		endwin();
		printf("Your terminal doesn't support colors.");
		return 1;
	}

	if(COLORS < 16) {
		endwin();
		printf("Your terminal doesn't support at least 16 colors.");
		return 1;
	}

	int i = 0;
	for (i = 0; i < 8; i++) {
		init_pair(i+1, i, -1);
		init_pair(i+9, i+8, -1);
	}
	for (i = 0; i < 8; i++) {
		attron(COLOR_PAIR(i+1));
		mvwprintw(stdscr,i,0,"Normal");
		attroff(COLOR_PAIR(i+1));
		attron(COLOR_PAIR(i+9));
		mvwprintw(stdscr,i,8,"Bright");
		attroff(COLOR_PAIR(i+9));
	}
	for (i = 0; i < 6; i++) {
		attron(COLOR_PAIR(i+1));
		mvwprintw(stdscr,i,15,"%s",white_glyphs[i]);
		mvwprintw(stdscr,i+6,15,"%s",black_glyphs[i]);
		attroff(COLOR_PAIR(i+1));
	}
	refresh();
	getch();
	endwin();
	return 0;
}
