CC=gcc
PROGS=scheduler
CFLAGS=-std=c99 
LFLAGS=-lm

all: $(PROGS)

shceduler.o: scheduler.c scheduler.h
	$(CC) $(CFLAGS) -c scheduler.c
	
my_queue.o: my_queue.c my_queue.h
	$(CC) $(CFLAGS) -c my_queue.c

scheduler: scheduler.o my_queue.o
	$(CC) $(CFLAGS) -o scheduler scheduler.o my_queue.o $(LFLAGS)
	
clean:
	rm -f *.o *.txt $(PROGS)