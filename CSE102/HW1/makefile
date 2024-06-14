all: clean compile run

compile: hw1.c util.c util.h
	@echo "Compiling..."
	@gcc -o test hw1.c util.c

run:
	@echo "Running the tests...."
	@./test
	@echo "Completed tests...."

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
