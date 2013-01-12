ARQUIVO=vmDoc
all: pdf cls
pdf:
	pdflatex mod_doc.tex
	pdflatex mod_doc.tex
	pdflatex mod_doc.tex
	mv mod_doc.pdf $(ARQUIVO).pdf
	evince $(ARQUIVO).pdf &
cls:
	rm -f *.out *.log *.aux *.bbl *.blg *.dvi *.lot *.toc *.lof *.*~
