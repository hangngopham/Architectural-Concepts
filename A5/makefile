all: test

test: test.o cache.o
	g++ -o test test.o cache.o

test.o: test.cpp cache.cpp cache.h
	g++ -c test.cpp

cache.o: cache.cpp cache.h
	g++ -c cache.cpp

clean: 
	rm -rf *.o expression




