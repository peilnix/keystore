#ifndef KEYSTORE_UTIL_H
#define KEYSTORE_UTIL_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Secure memset */
void zerobuf(void *, size_t);

int get_password(const char *prompt, char *, size_t);
int get_confirmed_password(const char *prompt1,
		const char *prompt2, char *, size_t);


#endif
