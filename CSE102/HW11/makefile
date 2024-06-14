all: clean compile run

compile: hw11.c
	@echo "*************************Compiling*************************"
	@gcc -o hw11 hw11.c -lm -lrt

run:
	@echo "*************************Running*************************"
	@./hw11

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f hw11

