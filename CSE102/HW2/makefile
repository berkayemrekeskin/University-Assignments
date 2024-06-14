all: clean compile run

compile: main.c
	@echo "*************************Compiling*************************"
	@gcc -o test main.c -lm

run:
	@echo "*************************Running*************************"
	@./test

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f test
