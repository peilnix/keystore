#include <signal.h>
#include <ncurses.h>
#include "keystore.h"

struct keystore {
	sqlite3 *db;
	char     path[512];

	WINDOW  *wtop;
	WINDOW  *wmenu;
	WINDOW  *wmain;
	WINDOW  *wfoot;

	ks_keylist keys;
	int done;
} KS;

static void KS_init(void);
static void KS_free(void);
static int  open_db(const char *path);
static void setup_win(void);

static void winadds(WINDOW *, int attr, const char *, int clear, int refr);
static int  wingetyx(WINDOW *, const char *


int keystore_run_ui(const char *dbfile)
{
	int c;
	KS_init();

	if (open_db(dbfile)) {
		ks_error("! Failed to open db\n");
		goto end;
	}

	setup_win();

	while (!KS.done) {

		c = wgetch(KS.wfoot);

		switch (c) {
		case 'q':
			KS.done = 1;
			break;
		}
	}

end:
	KS_free();
	return 0;
}


static void KS_init(void)
{
	KS.db = NULL;
	KS.wtop = KS.wmenu = KS.wmain = KS.wfoot = NULL;
	KS.done = 0;
	ks_keylist_init(&KS.keys);
}

static void KS_free(void)
{
	ks_keylist_free(&KS.keys);
	ks_db_close(KS.db);
	delwin(KS.wtop);
	delwin(KS.wmenu);
	delwin(KS.wmain);
	delwin(KS.wfoot);
	endwin();
}

static int open_db(const char *dbfile)
{
	char *home;
	char pass[32];
	int  res;

	if (!dbfile) {
		home = getenv("HOME");
		if (!home) {
			ks_error("! Failed to getenv('HOME')\n");
			return -1;
		}
		snprintf(KS.path, sizeof(KS.path), "%s/%s", home,
			KEYSTORE_DBFILE);
	} else {
		snprintf(KS.path, sizeof(KS.path), "%s", dbfile);
	}

	if (!ks_isreg(KS.path)) {
		printf(	"We are going to create the keystore database\n"
			"at '%s'\n\n", KS.path);
		res = ks_read_confirmed_pass("Enter db password: ",
				"Retype db password: ", pass, sizeof(pass));
		switch (res) {
			case -1:
				printf("Abort!\n");
				return -1;
			case -2:
				printf("Passwords mismatch!\n");
				return -1;
		}
	}
	else {
		res = ks_read_pass("Keystore password: ", pass, sizeof(pass));
		if (res != 0) return -1;
	}

	KS.db = ks_db_open(KS.path, pass);
	ks_zerobuf(pass, sizeof(pass));

	return (!KS.db) ? -1 : 0;
}

static void setup_win(void)
{
	int wh, ww;

	initscr();
	getmaxyx(stdscr, wh, ww);

	KS.wtop  = newwin(1,    ww,    0, 0);
	KS.wmenu = newwin(1,    ww,    1, 0);
	KS.wmain = newwin(wh-3, ww,    2, 0);
	KS.wfoot = newwin(1,    ww, wh-1, 0);

	wbkgd(KS.wtop,  A_REVERSE);
	wbkgd(KS.wfoot, A_REVERSE);

	noecho();
	curs_set(0);
	keypad(KS.wfoot, 1);


	winadds(KS.wtop, A_BOLD, KEYSTORE_RELEASE, 0, 0);
	winadds(KS.wfoot, A_BOLD, "db", 0, 0);
	waddstr(KS.wfoot, ": ");
	waddstr(KS.wfoot, KS.path);

	wrefresh(KS.wtop);
	wrefresh(KS.wmenu);
	wrefresh(KS.wmain);
	wrefresh(KS.wfoot);
}

static void winadds(WINDOW *w, int attr, const char *s,
		int clr, int refr)
{
	if (clr) wclear(w);
	if (attr != -1) wattron(w, attr);
	waddstr(w, s);
	if (attr != -1) wattroff(w, attr);
	if (refr) wrefresh(w);
}
