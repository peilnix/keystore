#include "key.h"


ks_key *ks_key_new(void)
{
	ks_key *k = (ks_key*)malloc(sizeof(ks_key));
	if (!k) {
		perror("! ks_key_new")
		return NULL;
	}
	k->user = k->host = k->pass = k->comment = NULL;
	k->prev = k->next = NULL;
	return k;
}

ks_key *ks_key_new_init(const char *user, const char *host,
		const char *pass, const char *comment)
{
	ks_key *k = ks_key_new();
	if (!k) return NULL;

}

void ks_key_free(ks_key *k)
{
	if (k) {
		if (k->user) free(k->user);
		if (k->host) free(k->host);
		if (k->pass) free(k->pass);
		if (k->comment) free(k->comment);
		free(k);
		k = NULL;
	}
}

int ks_key_set_user(ks_key *k, const char *s)
{
	if (!k || !s) return -1;
	if (k->user) free(k->user);

}

int ks_key_set_host(ks_key *, const char *);
int ks_key_set_pass(ks_key *, const char *);
int ks_key_set_comment(ks_key *, const char *);

