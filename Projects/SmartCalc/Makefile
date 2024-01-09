CC = gcc
CFLAGS := -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS := --coverage
SRC = $(wildcard backend/*.c)
OBJS = $(SRC:.c=.o)

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
  LIBS =  -lcheck -lm
else
  LIBS = -pthread -lcheck -lm -lrt -lsubunit
endif

all: clean install

s21_smart_calc.a: $(OBJS)
	ar rcs s21_smart_calc.a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_smart_calc.a
	$(CC) $(CFLAGS) ./test_log/s21_smart_calc_tests.c $< -o unit_test $(LIBS)
	./unit_test

gcov_report: $(SRC)
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC) ./test_log/s21_smart_calc_tests.c -o unit_test $(LIBS)
	./unit_test
	lcov -t "Report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	open ./report/index.html
	make clean_without_report

install: clean
	cd frontend && qmake && make && make clean && rm Makefile && mkdir ../build && mv SmartCalc.app/$(UI_BIN) ../build/

dvi:
	open ./README.md

dist: install
	mkdir -p dist
	cp  -R ./build/SmartCalc.app ./dist/SmartCalc.app
	cp ./README.md ./dist/README.md
	cd ./dist && tar cvzf SmartCalc.tgz *
	cd ./dist && rm -R SmartCalc.app README.md
	make clean

uninstall:
	rm -rf build

valg: clean test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./unit_test

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i **/*.c  **/*.cpp
	clang-format -i **/*.h
	rm -rf .clang-format

clean_without_report: 
	rm -rf *.o **/*.o *.gcno *.gcov *.gcda *.info *.a *.dSYM **/*.dSYM main_test unit_test gcov_unit_test

clean: clean_without_report
	rm -rf report test_log/*.log check