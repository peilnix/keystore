#include "win.h"

WINDOW *wtop  = NULL;
WINDOW *wmenu = NULL;
WINDOW *wmain = NULL;
WINDOW *wfoot = NULL;


void win_setup(void)
{
        int wh, ww;

        initscr();
        getmaxyx(stdscr, wh, ww);

        wtop  = newwin(1,    ww,    0, 0);
        wmenu = newwin(1,    ww,    1, 0);
        wmain = newwin(wh-3, ww,    2, 0);
        wfoot = newwin(1,    ww, wh-1, 0);

        wbkgd(wtop,  A_REVERSE);
        wbkgd(wfoot, A_REVERSE);

        noecho();
        curs_set(0);
        keypad(wmain, 1);
        keypad(wfoot, 1);


	win_adds(wtop, 0, 0, A_BOLD, KEYSTORE_RELEASE);
	win_adds(wfoot, 0, 0, A_BOLD, "db");
        waddstr(wfoot, ": ");
//        waddstr(wfoot, KS.path);

	win_refrall();
}

void win_free(void)
{
	delwin(wtop);
	delwin(wmenu);
	delwin(wmain);
	delwin(wfoot);
	endwin();
}

int win_getch(void)
{
	return wgetch(wfoot);
}

void win_adds(WINDOW *w, int clr, int refr, int attr, const char *s)
{
	if (clr)  wclear(w);
	if (attr) wattron(w, attr);
	waddstr(w, s);
	if (attr) wattroff(w, attr);
	if (refr) wrefresh(w);
}

void win_addf(WINDOW *w, int clr, int refr, int attr, const char *s, ...)
{
	char tmp[128];
	va_list val;
	va_start(val, s);
	vsnprintf(tmp, 128, s, val);
	va_end(val);
	win_adds(w, clr, refr, attr, tmp);
}

void win_clear(WINDOW *w, int refr)
{
	wclear(w);
	if (refr) wrefresh(w);
}

void win_clearall(int refr)
{
	wclear(wtop);
	wclear(wmenu);
	wclear(wmain);
	wclear(wfoot);
	if (refr)
		win_refrall();
}

void win_refrall(void)
{
	wrefresh(wtop);
	wrefresh(wmenu);
	wrefresh(wmain);
	wrefresh(wfoot);
}

void win_resize(void)
{
        int wh, ww;
        getmaxyx(stdscr, wh, ww);

	wresize(wtop, 1, ww);
	wresize(wmenu, 1, ww);
	wresize(wmain, wh-3, ww);
	wresize(wfoot, 1, ww);

	mvwin(wtop, 0, 0);
	mvwin(wmenu, 1, 0);
	mvwin(wmain, 2, 0);
	mvwin(wfoot, wh-1, 0);

	win_refrall();
}

