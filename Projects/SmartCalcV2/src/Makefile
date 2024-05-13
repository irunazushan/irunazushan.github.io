CXX = gcc
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 
LTEST = -lgtest

GCOVFLAGS = --coverage
SRC = $(wildcard model/*.cc)
OBJS = $(SRC:.cc=.o)

BUILD_DIR = ../build

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	APP_FILE := SmartCalcV2
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	APP_FILE := SmartCalcV2.app
	OPEN_CMD := open
endif


.PHONY: all

all: clean install

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBS)

valg: clean test
	valgrind --tool=memcheck --leak-check=yes ./test

leak:
	@echo "┏----------------------┓"
	@echo "┃   Checking to leaks  ┃"
	@echo "┗----------------------┛"
	leaks -atExit -- ./test

install: clean	
	@echo "┏-----------------------------┓"
	@echo "┃     Start installation      ┃"
	@echo "┗-----------------------------┛"
	mkdir -p $(BUILD_DIR)
	qmake -o $(BUILD_DIR)/Makefile view/SmartCalcV2.pro
	make -C $(BUILD_DIR)
	make -C $(BUILD_DIR) clean
	rm -rf $(BUILD_DIR)/.qmake.stash $(BUILD_DIR)/Makefile
	@echo "┏-------------------------------------------------┓"
	@echo "┃        The installation was successful          ┃"
	@echo "┃    The executable file is located in build      ┃"
	@echo "┗-------------------------------------------------┛"


uninstall:
	@echo "┏---------------------------------┓"
	@echo "┃     Uninstalling a program      ┃"
	@echo "┗---------------------------------┛"
	rm -rf $(BUILD_DIR)
	@echo "┏---------------------------------┓"
	@echo "┃    The programm is uninstalled  ┃"
	@echo "┗---------------------------------┛"

dist:
	@echo "┏---------------------------------┓"
	@echo "┃     Creating distribution       ┃"
	@echo "┗---------------------------------┛"
	tar -czvf SmartCalcV2.tgz README.md $(BUILD_DIR)/$(APP_FILE)
	@echo "┏------------------------------------┓"
	@echo "┃    Distribution tgz is ready       ┃"
	@echo "┗------------------------------------┛"
	
dvi:
	$(OPEN_CMD) ../README.md
	
gcov_report: clean
	@echo "┏------------------------------------┓"
	@echo "┃       Generating html report       ┃"
	@echo "┗------------------------------------┛"
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(SRC) tests/test.cc -o test $(LTEST) $(LIBS)
	./test
	lcov -t "Report" --ignore-errors inconsistent -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a *.dSYM tests/*.o
	@echo "┏-----------------------------┓"
	@echo "┃     HTML report is ready    ┃"
	@echo "┗-----------------------------┛"
	$(OPEN_CMD) ./report/index.html


tests: $(OBJS)
	@echo "┏-------------------┓"
	@echo "┃   Testing models  ┃"
	@echo "┗-------------------┛"
	$(CXX) $(CXXFLAGS) tests/test.cc $^ -o test $(LTEST) $(LIBS)
	./test

clang:
	@echo "┏------------------------------┓"
	@echo "┃    Clang format correction   ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -i **/*.cc **/*.h

clang_check:
	@echo "┏------------------------------┓"
	@echo "┃   Checnking to clang-format  ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -n **/*.cc **/*.h
	
clean:
	@echo "┏-----------------------------┓"
	@echo "┃   Deleting temporary files  ┃"
	@echo "┗-----------------------------┛"
	rm -rf *.o main test *.gcno *.gcda *.dSYM model/*.o view/*.o report
