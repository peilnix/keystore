#ifndef KEYSTORE_KEY_H
#define KEYSTORE_KEY_H 1

#include "util.h"


/* Key context can be part of a linked list.
 */
typedef struct ks_key
{
	const char *user;
	const char *host;
	const char *pass;
	const char *comment;

	struct ks_key *prev;
	struct ks_key *next;

} ks_key;


ks_key *ks_key_new(void);
ks_key *ks_key_new_init(const char *user,
			const char *host,
			const char *pass,
			const char *comment);
void ks_key_free(ks_key *);


/* Setters */
int ks_key_set_user(ks_key *, const char *);
int ks_key_set_host(ks_key *, const char *);
int ks_key_set_pass(ks_key *, const char *);
int ks_key_set_comment(ks_key *, const char *);



#endif
