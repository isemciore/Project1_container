CC = g++

FLAGS = -std=c++11 -g -Wall


test_vec.out: test_vec.cpp UIntVector.o UIntVector.h
	$(CC) $(FLAGS) test_vec.cpp UIntVector.o -o test_vec.out

UIntVector.o: UIntVector.cpp
	$(CC) $(FLAGS) -c UIntVector.cpp -o UIntVector.o


clean:
	 rm -f *.o *.out
