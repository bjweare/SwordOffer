SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)
BIN=$(OBJ:%.o=%)

CC=gcc
CFLAG=-Wall -g -c

.PHONY: all clean

all:$(BIN)

$(BIN):%:%.o
	$(CC) $^ -o $@

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $^ -o $@

clean:
	rm $(OBJ) $(BIN)
