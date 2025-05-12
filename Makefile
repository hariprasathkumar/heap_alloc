CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -O0

# Source files
SRCS = main.c heap.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
