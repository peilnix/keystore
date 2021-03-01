#include "keylist.h"


void ks_keylist_init(ks_keylist *l)
{
	l->head = l->tail = NULL;
	l->len  = 0;
}

void ks_keylist_free(ks_keylist *l)
{
	ks_key *p, *next;
	for (p = l->head; p!=NULL; p=next) {
		next = p->next;
		ks_key_free(p);
	}
	ks_keylist_init(l);
}

void ks_keylist_add(ks_keylist *l, ks_key *k)
{
	if (!l->head) {
		k->index = 0;
		l->head  = k;
		l->tail  = k;
	} else {
		k->index = l->tail->index+1;
		k->prev  = l->tail;
		l->tail->next = k;
		l->tail  = k;
	}
	l->len++;
}

void ks_keylist_del(ks_keylist *l, ks_key *k)
{
	ks_keylist_detach(l, k);
	ks_key_free(k);
}

void ks_keylist_detach(ks_keylist *l, ks_key *k)
{
	if (k == l->head)
		l->head = l->head->next;
	if (k == l->tail)
		l->tail = l->tail->prev;
	if (k->prev)
		k->prev->next = k->next;
	if (k->next)
		k->next->prev = k->prev;
	l->len--;
}

