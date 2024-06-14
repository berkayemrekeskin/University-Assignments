all: clean compile run

compile: hw10.c
	@echo "*************************Compiling*************************"
	@gcc -o hw10 hw10.c -lm -lrt

run:
	@echo "*************************Running*************************"
	@./hw10

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f hw10

