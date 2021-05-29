CFLAGS = -g -Wall
LDFLAGS = -lncurses

.PHONY: clean

all:
		gcc $(CFLAGS) demo.c -o demo $(LDFLAGS)

clean:
		rm -rf demo
