CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
OUTDIR = bin

main: src/sexpr.c test/main.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
