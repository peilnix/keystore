#include "key.h"


ks_key *ks_key_new(void)
{
	ks_key *k = (ks_key*)ks_alloc(sizeof(ks_key));
	k->user = k->host = k->pass = k->comment = NULL;
	k->index = -1;
	k->prev = k->next = NULL;
	return k;
}

ks_key *ks_key_new_init(const char *user, const char *host,
		const char *pass, const char *comment)
{
	ks_key *k = ks_key_new();
	ks_key_set_user(k, user);
	ks_key_set_host(k, host);
	ks_key_set_pass(k, pass);
	ks_key_set_comment(k, comment);

	return k;
}

void ks_key_free(ks_key *k)
{
	if (k) {
		ks_free(k->user);
		ks_free(k->host);
		if (k->pass) {
			ks_zerobuf(k->pass, strlen(k->pass));
			ks_free(k->pass);
		}
		ks_free(k->comment);
		ks_free(k);
	}
}

void ks_key_set_user(ks_key *k, const char *s)
{
	if (k && s) {
		ks_free(k->user);
		k->user = ks_strdup(s);
	}
}

void ks_key_set_host(ks_key *k, const char *s)
{
	if (k && s) {
		ks_free(k->host);
		k->host = ks_strdup(s);
	}
}
void ks_key_set_pass(ks_key *k, const char *s)
{
	if (k && s) {
		ks_free(k->pass);
		k->pass = ks_strdup(s);
	}
}
void ks_key_set_comment(ks_key *k, const char *s)
{
	if (k && s) {
		ks_free(k->comment);
		k->comment = ks_strdup(s);
	}
}

