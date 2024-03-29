CXX = gcc
CXXFLAGS := -Wall -Werror -Wextra -std=c++17
LIBS = -lstdc++ -lpthread -lm 
LTEST = -lgtest

all: test

leaks:
	leaks -atExit -- ./test


test: clean
	$(CXX) $(CXXFLAGS) tests/*.cc -o test $(LTEST) $(LIBS)
	./test

clang: clean
	clang-format -style=Google -i **/*.cc **/*.h **/*.tpp

check_clang:
	clang-format -style=Google -n **/*.cc **/*.h **/*.tpp

clean:
	rm -rf *.o test *.dSYM
