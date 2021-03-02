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


/* Comparing mode passed to ks_key_cmp(). */
enum ks_key_cmp_mode
{
	CMP_BY_USER = 0,
	CMP_BY_HOST,
	CMP_BY_PASS,
	CMP_BY_COMMENT
};

/* Compares two keys by their attributes user, host, pass
 * or comment, ascending or descending and return -1, 0, or +1
 * if A is lower, equal or higher to B.
 */
int ks_key_cmp(const ks_key *A, const ks_key *B,
		enum ks_key_cmp_mode mode,
		int ascend);

/* Swap two keys without touching the attributes (prev,next,index)
 */
//void ks_key_swap(ks_key *A, ks_key *B);

#endif
