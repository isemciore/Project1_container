#include <utility> // std::pair

#include "hello.h"

//#include <iostream>

int main (int argc, char* argv[]) {
  std::pair<const char *, int> p = parse_args (argc ,argv);

//	std::cout << p.first << "\n";
//	std::cout << p.second << "\n";
	

  if (p.second != -1)
    hello (p.first, p.second);
}
