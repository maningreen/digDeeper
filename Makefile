CC = gcc
LDFLAGS = -lraylib -lm -lpthread
SRC = src/*.c
OUT = digDeeper

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUT)
