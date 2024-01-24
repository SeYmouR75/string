CC=gcc
CFLAGS=-std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra
LIBS=-lcheck

OS=$(shell uname -s)
OS_NAME=$(OS)

ifeq ($(OS), Linux)
  OPEN_CMD = xdg-open
  LIBS += -lm
  OS_NAME=$(shell grep -o 'Ubuntu' /etc/os-release | head -n 1)
  ifeq ($(OS_NAME), Ubuntu)
    LIBS += -lsubunit -lrt -lpthread
  endif
  OS_NAME=$(shell grep -o 'Debian' /etc/os-release | head -n 1)
  ifeq ($(OS_NAME), Debian)
    LIBS = -lm `pkg-config --cflags --libs check`
  endif
endif

BUILD_DIR=build
SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))

TARGET_NAME=s21_test_string
TARGET=s21_test_string.exe

S21_MATH_LIB=../s21_string.a

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_MATH_LIB) -o $(BUILD_DIR)/$@ $(LIBS)

$(BUILD_DIR)/%.o: %.c    
	$(CC) $(CFLAGS) -c $< -o $@

gcov: gcov_flags $(TARGET)

gcov_flags:
	$(eval CFLAGS += -g3 --coverage)

clang_check:
	clang-format -style=Google -n *.c *.h

clang_format:
	clang-format -style=Google -i *.c *.h

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so 

clean_gcov:
	cd $(BUILD_DIR) && rm -rf *.gcno *.gcda

clean: clean_obj clean_gcov
	cd $(BUILD_DIR) && rm -rf *.txt
