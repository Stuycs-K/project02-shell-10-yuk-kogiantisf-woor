run: test
	@./test

compile test: test.o processor.o executor.o
	@gcc -o test test.o processor.o executor.o

test.o: test.c
	@gcc -c test.c

processor.o: processor.c processor.h
	@gcc -c processor.c

executor.o: executor.c executor.h
	@gcc -c executor.c

clean:
	@rm *.o
	@rm test
