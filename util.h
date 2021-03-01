#ifndef KEYSTORE_UTIL_H
#define KEYSTORE_UTIL_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>


/* Memory helpers */
void *ks_alloc(size_t);
void  ks_free(void *);
char *ks_strdup(const char *);
char *ks_strndup(const char *, size_t);
/* Secure memset */
void ks_zerobuf(void *, size_t);

/* Ask user to enter password (stdin) and return:
 *
 *  0  if two passwords given and equal
 * -1  if user quit
 */
int ks_read_pass(const char *prompt, char *, size_t);

/* Ask user to type password (stdin) twice and return:
 *
 *  0  if two passwords given and equal
 * -1  if user quit
 * -2  if passwords mismatch
 */
int ks_read_confirmed_pass(const char *prompt1,
		const char *prompt2, char *, size_t);


/* Returns true if path leads to a regular file.
 */
int ks_isreg(const char *path);


/* Write to stderr */
#define ks_error(s,...) \
	fprintf(stderr, (s), ##__VA_ARGS__)

#endif
