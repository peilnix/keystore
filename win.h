#ifndef KEYSTORE_WIN_H
#define KEYSTORE_WIN_H 1

#include <ncurses.h>
#include "config.h"
#include "util.h"

/* The keystore UI is made of four ncurses windows.
 *
 * +------------------------------------+
 * | wtop				|
 * +------------------------------------+
 * | wmenu				|
 * +------------------------------------+
 * | wmain				|
 * |					|
 * |					|
 * |					|
 * +------------------------------------+
 * | wfoot				|
 * +------------------------------------+
 */
extern WINDOW *wtop;
extern WINDOW *wmenu;
extern WINDOW *wmain;
extern WINDOW *wfoot;


void win_setup(void);
void win_free(void);

int win_getch(void);

void win_adds(WINDOW *, int clear, int refr,
		int attr, const char *s);
void win_addf(WINDOW *, int clear, int refr,
		int attr, const char *s, ...);


void win_clear(WINDOW *, int refr);
void win_clearall(int refr);
void win_refr(WINDOW *);
void win_refrall(void);
void win_resize(void);



#endif
