CC = gcc
CFLAGS = -Wall -ansi -pedantic


SRCS = src/main.c src/numbers.c ../strings/src/d_strings.c
HDRS = src/numbers.h
OBJS = $(SRCS:.c=.o)
TARGET = numbers.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -I../strings/src -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
