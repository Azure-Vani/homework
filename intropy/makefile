file = main
main.pdf: $(file).tex
	xelatex $(file).tex
.PHONY: clean
clean:
	rm -f $(file).{vrb,aux,log,nav,out,snm,toc}
