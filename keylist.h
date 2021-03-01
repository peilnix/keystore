#ifndef KEYSTORE_KEYLIST_H
#define KEYSTORE_KEYLIST_H 1

#include "key.h"

typedef struct ks_keylist
{
	ks_key *head;
	ks_key *tail;
	size_t  len;

} ks_keylist;


void ks_keylist_init(ks_keylist *);
void ks_keylist_free(ks_keylist *);

void ks_keylist_add(ks_keylist *, ks_key *);
void ks_keylist_del(ks_keylist *, ks_key *);
void ks_keylist_detach(ks_keylist *, ks_key *);


#endif
