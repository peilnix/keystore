#ifndef KEYSTORE_KEY_H
#define KEYSTORE_KEY_H 1

#include "util.h"


/* A struct representing a key context.
 */
typedef struct ks_key
{
	char  *user;
	char  *host;
	char  *pass;
	char  *comment;

	int    index;		// Index in list
	struct ks_key *prev;	// Previous key
	struct ks_key *next;	// Next key

} ks_key;

/* Create key context. */
ks_key *ks_key_new(void);
ks_key *ks_key_new_init(const char *user,
			const char *host,
			const char *pass,
			const char *comment);
void ks_key_free(ks_key *);


/* Setters */
void ks_key_set_user(ks_key *, const char *);
void ks_key_set_host(ks_key *, const char *);
void ks_key_set_pass(ks_key *, const char *);
void ks_key_set_comment(ks_key *, const char *);



#endif
