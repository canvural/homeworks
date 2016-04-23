CC = gcc

all: main.o ./libfdr/libfdr.a
	$(CC) -o main main.o ./libfdr/libfdr.a

clean:
	rm -f main *.o

.SUFFIXES: .c .o

.c.o:
	$(CC) $(INCLUDE) -g  -c  $*.c
