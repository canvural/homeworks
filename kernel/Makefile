PROJECTS = libstats.a
PROJECTD = libstatd.so
OBJECTS = stat.o
CFLAGS  =
# Code for getting the current directory
# see: http://stackoverflow.com/a/23324703/1561146
ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

all: static tests dynamic testd

.c.o:
	gcc -c $(CFLAGS) $<

static: stat.o
	ar rcs $(PROJECTS) stat.o

tests:
	gcc test.c -L. -lstats -lm -o tests

dynamic: stat.o
	gcc -c -fpic stat.c
	gcc -lm -shared -o $(PROJECTD) stat.o

testd:
	gcc -o testd test.c -L. -lstatd -lm -Wl,-rpath=$(ROOT_DIR)

clean:
	$(RM) tests testd $(PROJECTS) $(PROJECTD) $(OBJECTS) *.~
