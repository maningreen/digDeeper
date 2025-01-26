CC = gcc
LDFLAGS = -lraylib -lm -lpthread
SRC = src/*.c
OUT = digDeeper
OUTDIR = build/

program:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUTDIR)$(OUT)

buildProf:
	$(CC) $(SRC) $(LDFLAGS) -o $(OUTDIR)$(OUT) -p -pg

prof:
	gprof $(OUTDIR)$(OUT) > proc

clean:
	rm -rf $(OUTDIR)*
