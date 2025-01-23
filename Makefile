CC = gcc
LDFLAGS = -lraylib -lm
SRC = src/*.c
OUT = digDeeper

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUT)
