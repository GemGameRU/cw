CC = gcc
CFLAGS = -g -Wall -Og
SRC = $(wildcard *.c) $(wildcard **/*.c)
OBJ = $(SRC:.c=.o)
WIN_DEL = $(subst /,\,$(OBJ))
EXE = cw

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clear:
ifeq ($(OS), Windows_NT)
	del $(WIN_DEL) $(EXE).exe main.exe 2> NUL
else
	rm -rf $(OBJ) $(EXE) main
endif
