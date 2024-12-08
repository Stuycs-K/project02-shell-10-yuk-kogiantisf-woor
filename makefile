.PHONY: clean run compile

run: shell 
	@./shell

compile shell: main.o parse.o processor.o executor.o parse.o
	@gcc -o shell main.o parse.o processor.o executor.o

main.o: main.c
	@gcc -c main.c

parse.o: parse.c parse.h
	@gcc -c parse.c

processor.o: processor.c processor.h
	@gcc -c processor.c

executor.o: executor.c executor.h
	@gcc -c executor.c

clean:
	@rm shell
	@rm *.o

