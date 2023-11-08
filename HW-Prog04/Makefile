CC=gcc
PROGS=rps1
CFLAGS=-std=c99 -Wall -Wpedantic -g
LFLAGS=-lpthread

all: $(PROGS)

rps1: 
	$(CC) $(CFLAGS) -o rps1 ./rps_sockets.c $(LFLAGS)
clean:
	rm -f $(PROGS)