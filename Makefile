CC = gcc
LDFLAGS = -lraylib -lm -lpthread
SRC = src/*.c
OUT = digDeeper
OUTDIR = build/

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUTDIR)$(OUT)
