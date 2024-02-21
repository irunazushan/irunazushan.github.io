CC=gcc
FLAGS=-Wall -Werror -Wextra

.PHONY: s21_cat cat_test

all: s21_cat

s21_cat: s21_cat.c cat_options.c
	$(CC) $(FLAGS) s21_cat.c cat_options.c -o $@

cat_test:
	cp s21_cat cat_test/
	cd cat_test && bash run_test.sh
	make clean

rebuild: 
	make s21_cat
	clang-format -i *.c *.h 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	rm -f cat_test/s21_cat
