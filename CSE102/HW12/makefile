all: clean compile run

compile: hw12.c
	@echo "*************************Compiling*************************"
	@gcc -o hw12 hw12.c -lm -lrt

run:
	@echo "*************************Running*************************"
	@./hw12

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f hw12

