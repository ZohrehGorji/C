CC=gcc
DEFS=-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS=-Wall -g -std=c99 -pedantic $(DEFS)

all: mycompress

mycompress: mycompress.o
	$(CC) -o mycompress mycompress.o

mycompress.o: mycompress.c
	$(CC) $(CFLAGS) -c mycompress.c
	
clean:
	rm mycompress.o mycompress
	
	