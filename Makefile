CC=gcc
INCLUDES=./include/
SOURCES=./source/site.c ./source/utils.c
BINARY=./test
PROG=./source/main.c

all:
	$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) 

run:
	$(BINARY)


