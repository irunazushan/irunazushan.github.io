CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
LIBS=-lfcgi

PHONY.: all main

all: clean main

main:
	$(CC) $(CFLAGS) main.c -o main $(LIBS)
	./main
	#spawn-fcgi -p 5555 ./main

clang:
	 clang-format -i *.c

clean:
	@if [ -e main ]; then \
		rm main; \
	fi
