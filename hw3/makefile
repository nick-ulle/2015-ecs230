
CC?= clang
CFLAGS= -std=c99 -Wall -Wextra $(include)

ifeq ($(CC), icc)
	LDLIBS= -mkl=sequential
else
	LDLIBS= -lblas -llapack
endif

bin_dir= bin
src_dir= src
objects= $(patsubst %.c, %.o, $(wildcard $(src_dir)/*.c))

target = $(bin_dir)/poly

include= -I$(src_dir)

all: $(target)

# Link the main binary.
$(target): $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(bin_dir)/*

rebuild: clean all

.PHONY: all clean rebuild

# Automatically delete .o files.
.INTERMEDIATE: $(objects)

