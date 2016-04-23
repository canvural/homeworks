CC = gcc

all: queue list

queue:  test-queue.o list.o queue.o
	$(CC) -o queue test-queue.o list.o queue.o

list:  test-list.o list.o queue.o
	$(CC) -o list test-list.o list.o queue.o

test-queue.o:  test-queue.c list.c list.h queue.c queue.h
	$(CC) $(CFLAGS) -c test-queue.c

list.o:  list.c list.h
	$(CC) $(CFLAGS) -c list.c

queue.o:  queue.c queue.h list.c list.h
	$(CC) -c queue.c

clean:
	$(RM) list queue *.o *~
