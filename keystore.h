#ifndef KEYSTORE_H
#define KEYSTORE_H 1

#include "config.h"
#include "key.h"
#include "db.h"


/* Start ncurses userinterface.
 *
 * @param  dbfile    Path to database. If this is NULL
 *                   we use $HOME/.keystore.db instead.
 */
int keystore_run_ui(const char *dbfile);




#endif
