CFLAGS = -g -Wall -Og
OUTDIR = bin

main: src/sexpr.c test/main.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
