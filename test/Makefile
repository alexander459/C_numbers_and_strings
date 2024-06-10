CC = gcc
CFLAGS = -Wall -ansi -pedantic -I../lib/strings/src -I../lib/numbers/src
LDFLAGS =
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)
EXEC = test_program


all: $(EXEC)


$(EXEC): $(OBJS) ../lib/strings/src/d_strings.o ../lib/numbers/src/numbers.o
	$(CC) $(LDFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(EXEC)
	$(MAKE) -C ../lib/strings clean
	$(MAKE) -C ../lib/numbers clean

.PHONY: all clean