CC = g++

FLAGS = -std=c++11 -g -Wall
FLAGSTWO = -I cxxtest/

simple_test.out: simple_testrunner.cpp count_if_followed_by.o
	$(CC) $(FLAGS) simple_testrunner.cpp count_if_followed_by.o $(FLAGSTWO) -o simple_test.out

count_if_followed_by.o: count_if_followed_by.cpp
	$(CC) $(FLAGS) -c count_if_followed_by.cpp

clean:
	 rm -f *.o *.out
