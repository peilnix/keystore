#include "keystore.h"

/*
 * Keystore
 */
int main(int argc, char *argv[])
{
	const char *dbpath = NULL;

	if (argc > 1)
		dbpath = argv[0];


	keystore_run_ui(dbpath);
	return 0;
}




