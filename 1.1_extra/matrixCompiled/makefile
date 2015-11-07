rCC = g++
CC = clang++
FLAGS = -std=c++11 -g -Wall


main.out: matrix_cxxTest.cpp
	./cxxtest/cxxtestgen.pl --error-printer -o tests.cpp matrix_cxxTest.cpp
	$(CC) $(FLAGS) -o main.out -I cxxtest/ tests.cpp matrix8.o

clean:
	rm -f main.out 
	rm -f tests.cpp && clear

