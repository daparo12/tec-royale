CFLAGS = -g -Wall
LDFLAGS = -lncurses

.PHONY: clean

all:
		gcc $(CFLAGS) main.c my_thread.c my_thread.h my_sched.c my_sched.h config_parser.c play_clash_royale.c my_mutex.h my_mutex.c  gui.c  -o tec-royale $(LDFLAGS)

clean:
		rm -rf tec-royale
		
		
