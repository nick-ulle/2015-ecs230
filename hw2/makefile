
CC = clang
CFLAGS = -Wall -Wextra $(include)
LDLIBS = -lm

target = bin/mult
include = -I$(src_dir)

bin_dir = bin
src_dir = src
test_dir = tests
objects = $(patsubst %.c, %.o, $(wildcard $(src_dir)/*.c))
tests = $(patsubst %.c, %, $(wildcard $(test_dir)/*.c))

all: $(target)

# Link the main binary.
$(target): $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Run the tests.
tests: $(tests)

clean:
	rm -f $(target) $(tests)

rebuild: clean all

.PHONY: all tests clean rebuild

# Automatically delete .o files.
.INTERMEDIATE: $(objects)
