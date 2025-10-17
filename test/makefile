CC = gcc
CFLAGS = -Wall -Wextra -Wno-override-init -g -std=c99 -I. -I../src -I./Unity/src
TARGET = gd-dll-test

SOURCES = gd-dll-test.c ../src/gd-dll.c Unity/src/unity.c
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
