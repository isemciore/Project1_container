CC    = g++
#CC   = clang++-3.6 -L /usr/lib/gcc/x86_64-linux-gnu/4.8 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8 

FLAGS = -std=c++11 -g -Wall -pedantic

weird.out: weird.cpp
	 $(CC) $(FLAGS) weird.cpp -o weird.out

clean:
	rm -f *.o *.out
