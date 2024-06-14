all: clean compile run

compile: main.c
	@echo "*************************Compiling*************************"
	@gcc -o main main.c -lm -lrt

run:
	@echo "*************************Running*************************"
	@./main

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f main
