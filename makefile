.PHONY: clean run compile

run: main
	@./main

compile main: main.o parse.o processor.o executor.o parse.o
	@gcc -o main main.o parse.o processor.o executor.o

main.o: main.c parse.h
	@gcc -c main.c

parse.o: parse.c parse.h
	@gcc -c parse.c

processor.o: processor.c processor.h
	@gcc -c processor.c

executor.o: executor.c executor.h
	@gcc -c executor.c

clean:
	@rm *.o main

