#include <signal.h>
#include <ncurses.h>
#include "keystore.h"
#include "win.h"

struct keystore {
	sqlite3   *db;
	char       path[512];
	ks_keylist keys;
	int        done;
} KS;

static void KS_init(void);
static void KS_free(void);
static int  open_db(const char *path);


int keystore_run_ui(const char *dbfile)
{
	int c;
	KS_init();

	if (open_db(dbfile)) {
		ks_error("! Failed to open db\n");
		goto end;
	}

	win_setup();

	while (!KS.done) {

		c = win_getch();

		switch (c) {
		case KEY_RESIZE:
			win_resize();
			break;
		case KEY_UP:
		case KEY_DOWN:
		case 'n':
		case 'd':
		case 'u':
		break;
		case 'q':
			KS.done = 1;
			break;
		}
	}
end:
	win_free();
	KS_free();
	return 0;
}


static void KS_init(void)
{
	KS.db = NULL;
	KS.done = 0;
	ks_keylist_init(&KS.keys);
}

static void KS_free(void)
{
	ks_keylist_free(&KS.keys);
	ks_db_close(KS.db);
}

static int open_db(const char *dbfile)
{
	char *home;
	char pass[32];
	int  res;

	if (!dbfile) {
		// If no path is given, we use the default
		// keystore path "~/KEYSTORE_DBFILE"
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
		printf(	"We will create the keystore database\n"
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

