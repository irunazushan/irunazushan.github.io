CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11
LDFLAGS := -lcheck

BUILD_DIR := ../build
NAME_TASK := C8_3DVIEWER_V1.0-1

GTEST_FLAGS = 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes

MODEL_DIR := model
MODEL_SRC := $(wildcard $(MODEL_DIR)/*.c)
MODEL_OBJ := $(patsubst %.c,%.o,$(MODEL_SRC))

TEST_DIR := tests
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(patsubst %.c,%.o,$(TEST_SRC))
TEST_EXEC := s21_parser_test

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	LDFLAGS += -lpthread -lrt -lm -lsubunit
	APP_FILE := 3DViewer
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	LDFLAGS +=
	APP_FILE := 3DViewer.app
	OPEN_CMD := open
endif

all: clean install

install:
	@echo "┏=============================┓"
	@echo "┃    Start installation...    ┃"
	@echo "┗=============================┛"
	@mkdir -p $(BUILD_DIR)
	@qmake6 -o $(BUILD_DIR)/Makefile view/3DViewer.pro
	@make -C $(BUILD_DIR)
	@make -C $(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)/.qmake.stash $(BUILD_DIR)/Makefile
	@echo "┏=================================================┓"
	@echo "┃        The installation was successful.         ┃"
	@echo "┃    The executable file is located in build.     ┃"
	@echo "┗=================================================┛"

uninstall:
	@echo "┏=================================┓"
	@echo "┃    Uninstalling a program...    ┃"
	@echo "┗=================================┛"
	@rm -rf $(BUILD_DIR)

dvi:
	@$(OPEN_CMD) README.md

dist:
	@echo "┏=================================┓"
	@echo "┃    Creating distribution...     ┃"
	@echo "┗=================================┛"
	@tar -czvf 3DViewerV1.tgz README.md $(BUILD_DIR)/$(APP_FILE)
	@echo "┏====================================┓"
	@echo "┃    Distribution tgz is ready.      ┃"
	@echo "┗====================================┛"

gcov_report: clean
	@echo "┏====================================┓"
	@echo "┃     Generating html report ...     ┃"
	@echo "┗====================================┛"
	@$(CC) $(GCOV_FLAGS) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) $(LDFLAGS) -o $(TEST_EXEC)
	@./$(TEST_EXEC)
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory report
	@rm -f *.gcno *.gcda *.info $(TEST_EXEC)
	@echo "┏=========================================┓"
	@echo "┃     HTML report is ready. Opening...    ┃"
	@echo "┗=========================================┛"
	@$(OPEN_CMD) ./report/index.html &

tests:
	$(CC) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

valgrind:
	$(CC) $(CFLAGS) $(TEST_SRC) $(MODEL_SRC) $(GTEST_FLAGS) -o $(TEST_EXEC) $(LDFLAGS)
	valgrind $(VALGRIND_FLAGS) -s ./$(TEST_EXEC)

clang:
	@echo "┏=================================================┓"
	@echo "┃  Formatting code according to Google Style...   ┃"
	@echo "┗=================================================┛"
	@clang-format -i **/*.h **/*.c **/*.cc

clean:
	@echo "┏===============================┓"
	@echo "┃  Deleting temporary files...  ┃"
	@echo "┗===============================┛"
	@rm -rf $(TEST_EXEC)
	@rm -rf report

.PHONY: all install uninstall dvi dist gcov_report tests valgrind clang clean
