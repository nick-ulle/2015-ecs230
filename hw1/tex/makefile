
.PHONY: all clean rebuild

all: hw1.pdf

%.pdf: %.md
	pandoc --template=article -w latex -o $@ $<

clean:
	rm -f *.pdf

rebuild: clean all

