CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Os -ggdb

all: serialize deserialize

clean: serialize deserialize
	rm $^

deserialize: deserialize.c
	$(CC) -o $@ $^ $(CFLAGS)

serialize: serialize.c
	$(CC) -o $@ $^ $(CFLAGS)
