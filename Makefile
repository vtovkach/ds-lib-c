
CC := gcc
CFLAGS := -Wall -Wextra -g -Iinclude

# Source and object files 
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))

# Static library output 
LIB := lib/libds_lib.a

#Test sources and binaries 
TEST_SRC := $(wildcard tests/*.c)
TEST_BIN := $(patsubst tests/%.c, bin/%, $(TEST_SRC))

# Default build target 
all: $(LIB)

#Build static library 
$(LIB): $(OBJ)
	@mkdir -p lib
	ar rcs $@ $^

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Compile all test executables
compile-tests: $(TEST_BIN)

# Pattern rule to compile each test source to an executable
bin/%: tests/%.c $(LIB)
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -Llib -lds_lib -o $@

clean:
	rm -rf build lib bin
