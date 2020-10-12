CC=gcc
INCLUDES=./include/
SOURCES=./source/site.c ./source/pchave.c ./source/lista_pchave.c ./source/listaencadeada.c 
BINARY=./test
PROG=./source/main.c

all:
	$(CC) -g -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) 

run:
	$(BINARY)


