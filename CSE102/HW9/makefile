all: clean compile run

compile: hw9.c
	@echo "*************************Compiling*************************"
	@gcc -o hw9 hw9.c -lm -lrt

run:
	@echo "*************************Running*************************"
	@./hw9

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f hw9

