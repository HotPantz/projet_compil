//Selyan Kablia et Nathan Lestrade

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c lexer.c parser.c evaluator.c
OBJS = $(SRCS:.c=.o)

calc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJS) calc
