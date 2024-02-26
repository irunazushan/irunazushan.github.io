CXX = gcc
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 
LTEST = -lgtest
GCOVFLAGS = --coverage
SRC = methods.cc operations.cc operators.cc other.cc
OBJS = $(SRC:.cc=.o)

.PHONY: all test

all: clean test

s21_matrix_oop.a: $(OBJS)
	ar rcs s21_matrix_oop.a $(OBJS) 

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBS)

valg:
	valgrind --tool=memcheck --leak-check=yes ./test

leak:
	leaks -atExit -- ./test

gcov_report: $(SRC)
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $^ test.cc -o test $(LTEST) $(LIBS)
	./test
	lcov -t "Report" --ignore-errors mismatch -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	open ./report/index.html
	make clean_for_report


test: s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) test.cc $< -o test $(LTEST) $(LIBS)
	./test

clang:
	clang-format -style=Google -i *.cc *.h

check_clang:
	clang-format -style=Google -n *.cc *.h

clean_for_report:
	rm -rf *.gcno *.gcov *.gcda *.info *.a *.dSYM *.o

clean: clean_for_report
	rm -rf *.o report test main s21_matrix_oop.a *.dSYM