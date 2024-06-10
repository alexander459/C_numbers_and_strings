CC = gcc
CFLAGS = -Wall -ansi -pedantic -g


TARGET = strings.exe
SRCS = src/main.c src/d_strings.c
HDRS = src/d_strings.h
OBJS = $(SRCS:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJS) 

.PHONY: all run clean
