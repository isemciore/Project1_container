CC = g++
FLAGS = -std=c++11 -g -Wall


all: birth.out bad_plumming.out

birth.out: birth.cpp
	$(CC) $(FLAGS) birth.cpp -o birth.out

bad_plumming.out: bad_plumming.cpp
	$(CC) $(FLAGS) bad_plumming.cpp -o bad_plumming.out

clean:
	rm -f *.o *.out
