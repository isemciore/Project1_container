CC = g++

FLAGS = -std=c++11 -g -Wall

MAIN = main

main.out: Vector.h main.cpp boolVector.o boolVector.hpp
	$(CC) $(FLAGS) $(MAIN).cpp boolVector.o -o $(MAIN).out

boolVector.o: boolVector.cpp
	$(CC) $(FLAGS) -c boolVector.cpp -o boolVector.o


clean:
	rm -f *.o *.out && clear 

