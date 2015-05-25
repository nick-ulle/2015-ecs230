
target = hw3.pdf
template = article

all: $(target)

%.pdf: %.tex
	pdflatex --fmt=$(template) --shell-escape $*
	rm -f $< *.aux *.out *.log

%.tex: %.md
	pandoc --template=$(template) -w latex -o $@ $<
	parblock $@ %.tmp
	mv %.tmp $@

clean:
	rm -f $(target)

rebuild: clean all

.PHONY: all clean rebuild
