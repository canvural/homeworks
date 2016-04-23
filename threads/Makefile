PROJ=thread
SOURCES=main.c threadpool.c mysql_helper.c

CC=gcc

CFLAGS=-std=c99 -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG
LIBS= -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl

$(PROJ): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm $(PROJ)
