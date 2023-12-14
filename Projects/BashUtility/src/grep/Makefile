CC=gcc
FLAGS=-Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.c grep_options.c
	$(CC) $(FLAGS) s21_grep.c grep_options.c -o $@

rebuild: 
	make s21_grep
	clang-format -i *.c *.h 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
