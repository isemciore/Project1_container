#include <iostream>
#include <utility>
//#include <pair>
#include <cstdlib>
#include <locale> 
#include "hello.h"

void hello (const char * name, int count) {
  if (count > 0){
	std::cout << "Hello,";
    
    for(int i = 1; i <= count; i++){
		std::cout << " " <<name;
	}
	std::cout <<"!\n";
	}
}

std::pair<const char *, int> parse_args (int argc, char * argv[]) {
  // TODO
  const char * name = argv[1];
  std::locale loc;
  int repeat = 0;
	if(3==argc){
		if(isdigit(* argv[2],loc)){
			repeat = std::atoi(argv[2]);
		}
		else{
			std::cerr << "2nd argument must be an integral greater than zero!" << "\n";
			repeat = -1;
		}
	}
	
	else if (argc > 3){
	  std::cerr << "Too many arguments!" <<"\n";
	  repeat = -1;
	}
	else if (argc == 2){
		repeat = 1;
	}
	else if (argc ==1){
		name = "world";
		repeat = 1;
	}
  return std::make_pair (name, repeat);
}
