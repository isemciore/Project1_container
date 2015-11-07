rCC = g++
CC = clang++

FLAGS = -std=c++11 -g -Wall -pedantic -pthread

testOUT = main
arrayNa = Vector


$(testOUT).out: $(testOUT).cpp $(arrayNa).hpp SafeVector1.hpp SafeVectPar.hpp
	$(CC) $(FLAGS) $(testOUT).cpp  -o $(testOUT).out


clean:
	rm -f *.o *.out && clear 

