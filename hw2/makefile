
#CC= clang
CC = icc
CFLAGS= -Wall -Wextra $(include)
#LDLIBS=

bin_dir= bin
src_dir= src
objects= $(patsubst %.c, %.o, $(wildcard $(src_dir)/*.c))
test_dir= tests
tests= $(patsubst %.c, %, $(wildcard $(test_dir)/*.c))

task1= bin/task1
task1_dir= $(src_dir)/task1
task1_objects= $(patsubst %.c, %.o, $(wildcard $(task1_dir)/*.c))

task2= bin/task2
task2_dir= $(src_dir)/task2
task2_objects= $(patsubst %.c, %.o, $(wildcard $(task2_dir)/*.c))

include= -I$(src_dir) -I$(task1_dir) -I$(task2_dir)

all: task1 task2
task1: $(task1)
task2: $(task2)

# Link the main binary.
$(task1): $(objects) $(task1_objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(task2): $(objects) $(task2_objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -mkl=sequential

# Run the tests.
tests: $(tests)

$(tests): $(objects) $(task1_dir)/multiply.o

clean:
	rm -f $(task1) $(task2) $(tests)

rebuild: clean all

.PHONY: all tests clean rebuild

# Automatically delete .o files.
.INTERMEDIATE: $(objects) $(task1_objects) $(task2_objects)

