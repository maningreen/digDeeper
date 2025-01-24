CC = gcc
LDFLAGS = -lraylib -lm -lpthread
SRC = src/*.c
OUT = digDeeper

PROFILEFLAGS = -p -pg

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUT)

buildProf:
	$(CC) $(SRC) $(LDFLAGS) $(PROFILEFLAGS) -o $(OUT)

makeProf:
	gprof $(OUT) > prof
