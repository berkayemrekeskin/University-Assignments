all: clean compile

compile: hw8.c
	@echo "*************************Compiling*************************"
	@gcc -o hw8 hw8.c -lm -lrt
	@ulimit -s 1048512 && ./hw8

clean:
	@echo "*************************Cleaning*************************"
	@rm -f *.o
	@rm -f hw8
