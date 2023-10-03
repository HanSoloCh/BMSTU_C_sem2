CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -I./inc

LIB_FLAGS := -lcheck -lm #-lsubunit

OBJ_FILES := ./out/func.o ./out/input_output.o

SRC_DIR := ./src
OBJ_DIR := ./out
UNIT_DIR := ./unit_tests
HEAD_DIR := ./inc

APP_NAME := app.exe

RM_FILES := *.o *.exe a.out ./out

app.exe: $(OBJ_FILES) $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

unit_tests.exe: $(OBJ_DIR)/check_main.o $(OBJ_DIR)/check_func.o $(OBJ_DIR)/func.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIB_FLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(HEAD_DIR)/error_codes.h $(HEAD_DIR)/func.h $(HEAD_DIR)/input_output.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/func.o: $(SRC_DIR)/func.c $(HEAD_DIR)/func.h $(HEAD_DIR)/error_codes.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/input_output.o: $(SRC_DIR)/input_output.c $(HEAD_DIR)/input_output.h $(HEAD_DIR)/error_codes.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/check_main.o: $(UNIT_DIR)/check_main.c $(HEAD_DIR)/check_func.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/check_func.o: $(UNIT_DIR)/check_func.c $(HEAD_DIR)/check_func.h $(HEAD_DIR)/func.h $(HEAD_DIR)/error_codes.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

unit: unit_tests.exe
	./unit_tests.exe

release: CFLAGS += -O3
release: app.exe

debug: CFLAGS += -g3 -O0 --coverage
debug: app.exe

coverage:
	make -s coverage_quiet

coverage_quiet: debug func_tests
coverage_quiet:
	./func_tests/scripts/collect_coverage.sh

asan_debug: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -O0 -g3
asan_debug: app.exe

msan_debug: CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer -O0 -g3
msan_debug: CC := clang
msan_debug: app.exe

ubsan_debug: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer -O0 -g3
ubsan_debug: app.exe

func_tests:
	./func_tests/scripts/func_tests.sh

test_all:
	./func_tests/scripts/test_all.sh

valgrind:
	./func_tests/scripts/func_tests.sh -l


.PHONY: clean release debug asan_debug msan_debug ubsan_debug coverage coverage_quiet func_tests unit
clean:
	rm -rf $(RM_FILES)