CC = g++

FLAGS = -std=c++11 -g -Wall -pedantic

testOUT = main

$(testOUT).out: $(testOUT).cpp hyper.h 
	$(CC) $(FLAGS) $(testOUT).cpp  -o $(testOUT).out


clean:
	rm -f *.o *.out && clear 

