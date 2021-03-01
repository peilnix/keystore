#ifndef KEYSTORE_DB_H
#define KEYSTORE_DB_H 1

#define SQLITE_HAS_CODEC
#include <sqlcipher/sqlite3.h>

#include "util.h"
#include "keylist.h"

/* Open keystore database.
 * Note, that the database will be created if given path
 * does not exist.
 */
sqlite3 *ks_db_open(const char *path, const char *pass);
void     ks_db_close(sqlite3 *);

int ks_db_select_all_keys(sqlite3 *, ks_keylist *);
int ks_db_insert_key(sqlite3 *, const ks_key *);


#endif
