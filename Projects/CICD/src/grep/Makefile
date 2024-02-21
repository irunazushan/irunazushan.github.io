CC=gcc
FLAGS=-Wall -Werror -Wextra

.PHONY: s21_grep grep_test

all: s21_grep

s21_grep: s21_grep.c grep_options.c
	$(CC) $(FLAGS) s21_grep.c grep_options.c -o $@

grep_test:
	cp s21_grep grep_test/
	cd grep_test && bash run_test.sh
	make clean

rebuild: 
	make s21_grep
	clang-format -i *.c *.h 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	rm -f grep_test/s21_grep
