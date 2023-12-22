CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -Wall -Werror -Wextra --coverage
SRC = another.c arithmetic.c comparison.c convertors.c big_dec.c
OBJS = $(SRC:.c=.o)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
  LIBS =  -lcheck -lm -lrt -lpthread -lsubunit
else ifeq ($(OS),Darwin)
  LIBS = -lcheck -lm -lpthread
endif

all: gcov_report s21_decimal.a test

gcov_report: clean decimal_tests.c $(SRC)
	$(CC) $(GCOVFLAGS) -c $(SRC) 
	ar rcs s21_decimal.a $(OBJS)
	$(CC) $(GCOVFLAGS) -c decimal_tests.c -o decimal_tests.o
	$(CC) $(GCOVFLAGS) decimal_tests.o s21_decimal.a -o gcov_unit_test $(LIBS)
	./gcov_unit_test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html
	make clean_without_report

test: s21_decimal.a decimal_tests.o 
	$(CC) $(CFLAGS) decimal_tests.o s21_decimal.a -o unit_test $(LIBS)
	./unit_test

decimal_tests.o: decimal_tests.c
	$(CC) $(CFLAGS) -c decimal_tests.c -o decimal_tests.o

s21_decimal.a: $(OBJS)
	ar rcs s21_decimal.a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean_without_report: 
	rm -f  *.o *.gcno *.gcov *.gcda *.info *.a main_test unit_test gcov_unit_test

clean: clean_without_report
	rm -rf report