CC = gcc
LDFLAGS = -lraylib -lm -lpthread
SRC = src/*.c
OUT = digDeeper
OUTDIR = build/

PROFILEFLAGS = -p -pg

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUTDIR)$(OUT)

buildProf:
	$(CC) $(SRC) $(LDFLAGS) $(PROFILEFLAGS) -o $(OUT)

makeProf:
	gprof $(OUT) > prof
