CC     = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
CLIBS  = -lsqlcipher -lncurses
PROG   = keystore

$(PROG): main.c db.o key.o keylist.o keystore.o util.o win.o

	$(CC) $(CFLAGS) $(CLIBS) -o $(PROG)\
         main.c db.o key.o keylist.o keystore.o util.o win.o


key.o: key.c
	$(CC) $(CFLAGS) -c key.c
keylist.o: keylist.c
	$(CC) $(CFLAGS) -c keylist.c
keystore.o: keystore.c
	$(CC) $(CFLAGS) -c keystore.c
db.o: db.c
	$(CC) $(CFLAGS) -c db.c
util.o: util.c
	$(CC) $(CFLAGS) -c util.c
win.o: win.c
	$(CC) $(CFLAGS) -c win.c


clean:
	 rm -rf *.o $(PROG)

