CC=gcc
CFLAGS=-O2 -pthread
SRC=src/main.c
OBJ=simulador

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ)
