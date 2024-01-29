CC=gcc
CFLAGS=-std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra

TEST_DIR=tests
TEST_EXE=s21_test_string.exe
BUILD_DIR=./build
REPORT_DIR=./report

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif
ifeq ($(wildcard $(REPORT_DIR)), )
  $(shell mkdir $(REPORT_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))
TARGET=s21_string.a

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: %.c   
	$(CC) $(CFLAGS) -c $< -o $@ 

test: clean $(TARGET)
	cd $(TEST_DIR) && make
	cd $(TEST_DIR) && $(BUILD_DIR)/$(TEST_EXE)
#	cd $(TEST_DIR) && valgrind --tool=memcheck --leak-check=yes $(BUILD_DIR)/$(TEST_EXE)

gcov_report: clean gcov_flags $(TARGET)	
	cd $(TEST_DIR) && make gcov
	cd $(TEST_DIR) && $(BUILD_DIR)/$(TEST_EXE)
	cd $(REPORT_DIR) && lcov -t "coverage_report" -o s21_math.info -c -d ../$(BUILD_DIR) -d ../$(TEST_DIR)/$(BUILD_DIR)
	cd $(REPORT_DIR) && genhtml s21_math.info
	cd $(REPORT_DIR) && open index.html

gcov_flags: 
	$(eval CFLAGS += -g3 --coverage)

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.a 

clean_gcov:
	cd $(BUILD_DIR) && rm -rf *.gcno *.gcda
	rm -rf $(REPORT_DIR)/*

clean: clean_obj clean_gcov
	cd $(TEST_DIR) && make clean

clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -n *.c *.h
	cd $(TEST_DIR) && make clang_check
	rm -rf .clang-format

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -i *.c *.h
	cd $(TEST_DIR) && make clang_format
	rm -rf .clang-format

rebuild: clean all
