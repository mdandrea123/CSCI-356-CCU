CC = gcc
PROGS = rps
CFLAGS = -Wall -g -Wpedantic -std=c99

all: $(PROGS)

rps:
	$(CC) $(CFLAGS) -o rps ./rps_pipes.c

clean:
	rm -f -r $(PROGS) rps.dSYM
