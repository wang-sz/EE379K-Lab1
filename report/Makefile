PAPER = report
TEX = $(wildcard *.tex)
FLAGS = --shell-escape

.PHONY: all clean

$(PAPER).pdf: $(TEX)
	pdflatex $(FLAGS) $(PAPER)

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.fls *.fdb_latexmk 
# $(PAPER).pdf 
