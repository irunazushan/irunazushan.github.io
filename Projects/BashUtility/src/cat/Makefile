CC=gcc
FLAGS=-Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.c cat_options.c
	$(CC) $(FLAGS) s21_cat.c cat_options.c -o $@

rebuild: 
	make s21_cat
	clang-format -i *.c *.h 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
