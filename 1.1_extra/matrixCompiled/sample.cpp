#include "matrix.hpp"
#include <iostream>
#include <sstream>

int main () {
  {
    Matrix m;
    Matrix n;

    std::istringstream (" [ 1 3 5 ; 2 4  6 ; 42 43 44 ] ") >> m;
    std::istringstream (" [ 1 8 9 ; 2 7 10 ;  3  6 11 ]")  >> n;

    std::cout << "------------- sub \n";
    std::cout << "m = " << m;
    std::cout << "n = " << n;
    std::cout << "r = " << (m-n) << std::endl;
  }

  {
    Matrix m (2, 2);
    Matrix n (2, 2);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    n[0][0] = 5;
    n[0][1] = 5;
    n[1][0] = 5;
    n[1][1] = 5;

    std::cout << "------------- add\n";
    std::cout << "m = " << m;
    std::cout << "n = " << n;
    std::cout << "r = " << (m+n) << std::endl;
  }


}
