tCC = g++
CC = clang++

FLAGS = -std=c++11 -g -Wall -pedantic

testOUT = main
arrayNa = Vector


$(testOUT).out: $(testOUT).cpp $(arrayNa).h 
	$(CC) $(FLAGS) $(testOUT).cpp  -o $(testOUT).out


clean:
	rm -f *.o *.out && clear 

