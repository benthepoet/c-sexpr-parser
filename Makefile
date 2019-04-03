CC = gcc
CFLAGS = -g -Wall -Werror -Og
OUTDIR = bin

main: src/sexpr.c test/main.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
