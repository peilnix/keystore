#include "util.h"


void *ks_alloc(size_t n)
{
	void *x = malloc(n);
	if (!x) {
		perror("!ks_alloc");
		exit(EXIT_FAILURE);
	}
	return x;
}

void ks_free(void *x)
{
	if (x) free(x);
}

char *ks_strdup(const char *s)
{
	return (!s) ? NULL : ks_strndup(s,strlen(s));
}

char *ks_strndup(const char *s, size_t n)
{
	char *x = (char*)ks_alloc(n+1);
	strncpy(x, s, n);
	x[n] = '\0';
	return x;
}

void ks_zerobuf(void *x, size_t n)
{
	volatile char *p = x;
	while (n--) *p++ = 0;
}

int ks_read_pass(const char *prompt, char *pass, size_t max)
{
	size_t len;
        struct termios old, tnew;
	int fd_stdin = 0; // Since std=c99 does not allow fileno()
        memset(pass, 0, max);

        if (prompt) fputs(prompt, stdout);
        if (tcgetattr(fd_stdin, &old) != 0)
                return -1;
        tnew = old;
        tnew.c_lflag &= ~ECHO;
        if (tcsetattr(fd_stdin, TCSAFLUSH, &tnew) != 0)
                return -1;

        fgets(pass, max, stdin);
        tcsetattr(fd_stdin, TCSAFLUSH, &old);
        len = strlen(pass);
        if (len > 0) pass[--len] = 0;

	putchar('\n');
        return (len > 0) ? 0 : -1;
}

int ks_read_confirmed_pass(const char *prompt1, const char *prompt2,
		char *pass, size_t n)
{
	int  res;
	char tmp[n];

	res = ks_read_pass(prompt1, tmp, n);
	if (res != 0) goto error;

	res = ks_read_pass(prompt2, pass, n);
	if (res != 0) goto error;

	res = strcmp(tmp, pass);
	if (res != 0) {
		res = -2;
		goto error;
	}

	ks_zerobuf(tmp, n);
	return 0;
error:
	ks_zerobuf(tmp, n);
	ks_zerobuf(pass, n);
	return res;
}


int ks_isreg(const char *path)
{
	struct stat st;
	return (!stat(path, &st) && S_ISREG(st.st_mode));
}

int ks_strcmp(const char *A, const char *B)
{
	if (!A) {
		return (!B) ? 0 : -1;
	}
	else if (!B) {
		return (!A) ? 0 : +1;
	}
	return strcmp(A, B);
}

