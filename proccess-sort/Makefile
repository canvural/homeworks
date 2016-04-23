CC = gcc

all: rgen psort ipcsort

rgen:  rgen.o
	$(CC) -o rgen rgen.o -lm

psort:  psort.o
	$(CC) -o psort psort.o

ipcsort:  ipcsort.o
	$(CC) -o ipcsort ipcsort.o -lrt

rgen.o:  rgen.c
	$(CC) -c rgen.c

psort.o:  psort.c
	$(CC) -c psort.c

ipcsort.o:  ipcsort.c
	$(CC) -c ipcsort.c

clean:
	$(RM) rgen psort ipcsort *.o *.txt *.~
