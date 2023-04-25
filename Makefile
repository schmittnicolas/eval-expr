CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wvla -Wextra -D_POSIX_C_SOURCE=200809L

SRC = src/evalexpr.c src/stack.c src/fifo_access.c

all: evalexpr

evalexpr:
	$(CC) $(CFLAGS) src/main.c $(SRC) -o evalexpr -fsanitize=address -g

check:
	$(CC) $(CFLAGS) tests/testsuite.c $(SRC) -o testsuite -lcriterion
	./testsuite

.PHONY: all evalexpr check clean

clean:
	${RM} evalexpr
	${RM} testsuite
