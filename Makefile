CC     = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
CLIBS  = -lsqlcipher -lncurses
PROG   = keystore

$(PROG): main.c key.o util.o

	$(CC) $(CFLAGS) $(CLIBS) -o $(PROG)\
         main.c key.o util.o


key.o: key.c
	$(CC) $(CFLAGS) -c key.c
#db.o: db.c
#	$(CC) $(CFLAGS) -c db.c
util.o: util.c
	$(CC) $(CFLAGS) -c util.c


clean:
	 rm -rf *.o $(PROG)

