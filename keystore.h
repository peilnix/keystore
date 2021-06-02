#ifndef KEYSTORE_H
#define KEYSTORE_H 1

#include "config.h"
#include "key.h"
#include "db.h"

/*
 * up/down	Select key
 * enter	En/Disable showing password
 * n		Add new key
 * d		Delete selected key
 * u		Update selected key
 *
 */

/* Start ncurses user interface.
 *
 * @param  dbfile    Path to database. If this is NULL
 *                   we use $HOME/.keystore.db instead.
 */
int keystore_run_ui(const char *dbfile);




#endif
