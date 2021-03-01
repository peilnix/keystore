#include "db.h"

#define SQL_CREATE \
        "CREATE TABLE IF NOT EXISTS keys ("\
        "       user VARCHAR NOT NULL,"\
        "       host VARCHAR,"\
        "       pass VARCHAR NOT NULL,"\
        "       comment VARCHAR"\
        ");"

#define SQL_CHECKPASS \
	"SELECT count(*) FROM sqlite_master;"

static sqlite3 *openDB(const char *path, const char *pass);
static sqlite3 *createDB(const char *path, const char *pass);
static sqlite3_stmt *prepare(sqlite3 *db, const char *query);

sqlite3 *ks_db_open(const char *path, const char *pass)
{
	return ks_isreg(path) ?
		openDB(path, pass) :
		createDB(path, pass);
}

void ks_db_close(sqlite3 *db)
{
	if (db) sqlite3_close(db);
}

int ks_db_select_all_keys(sqlite3 *db, ks_keylist *list)
{
	sqlite3_stmt *stmt;
	ks_key       *key;

	stmt = prepare(db, "SELECT * FROM keys;");
	if (!stmt) return -1;

	while (sqlite3_step(stmt) == SQLITE_ROW) {

		key = ks_key_new_init(
			(char*)sqlite3_column_text(stmt, 0),
			(char*)sqlite3_column_text(stmt, 1),
			(char*)sqlite3_column_text(stmt, 2),
			(char*)sqlite3_column_text(stmt, 3));
		ks_keylist_add(list, key);
	}
	sqlite3_finalize(stmt);
	return 0;
}

int ks_db_insert_key(sqlite3 *db, const ks_key *k)
{
	int res;
	sqlite3_stmt *stmt;

	stmt = prepare(db, "INSERT INTO keys (user,host,pass,comment)"
			" VALUES (?,?,?,?);");
	if (!stmt) return -1;

	sqlite3_bind_text(stmt, 1, k->user, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 1, k->host, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 1, k->pass, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 1, k->comment, -1, SQLITE_STATIC);

	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return (res == SQLITE_DONE) ? 0 : -1;
}


static sqlite3 *openDB(const char *path, const char *pass)
{
	sqlite3 *db;
	if (sqlite3_open(path, &db) != 0) {
		ks_error("! Failed to open db '%s'\n", path);
		return NULL;
	}
	sqlite3_key(db, pass, strlen(pass));
	if (sqlite3_exec(db, SQL_CHECKPASS, 0, 0, 0) != SQLITE_OK) {
		ks_error("! Permission denied for db '%s'\n", path);
		ks_db_close(db);
		return NULL;
	}
	return db;
}
static sqlite3 *createDB(const char *path, const char *pass)
{
	sqlite3 *db = openDB(path, pass);
	if (!db)
		return NULL;
	else if (sqlite3_exec(db, SQL_CREATE, 0, 0, 0) != SQLITE_OK) {
		ks_error("! Failed to exec SQL_CREATE\n");
		ks_db_close(db);
		return NULL;
	}
	return db;
}
static sqlite3_stmt *prepare(sqlite3 *db, const char *query)
{
	sqlite3_stmt *st;
        return sqlite3_prepare_v2(db, query, -1, &st, 0) ? NULL : st;
}
