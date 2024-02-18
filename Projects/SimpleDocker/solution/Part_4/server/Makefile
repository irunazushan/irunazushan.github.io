CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
LIBS=-lfcgi

PHONY.: all main

all: clean port_cleaner main

main:
	$(CC) $(CFLAGS) main.c -o main $(LIBS)
	spawn-fcgi -p 8080 ./main

clang:
	 clang-format -i *.c

port_cleaner:
	@echo "Attempting to clean up process on port  8080..."
	@sudo fuser -k  8080/tcp || echo "This port is free for using."

clean:
	@if [ -e main ]; then \
		rm main; \
	fi
