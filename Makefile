CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Og
OUTDIR = bin

main: src/sexpr.c test/main.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^
