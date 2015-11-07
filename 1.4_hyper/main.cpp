#include <iostream>
#include "hyper.h"
using namespace std;
int main(){
    hypercube<3> n(7);

    hypercube<6> m(5);

    m[1][3][2][1][4][0] = 7;


    hypercube<3> t(5);
    t = m[1][3][2];
    t[1][4][0] = 2;
    std::cout << m[1][3][2][1][4][0] << "\n";
    std::cout << t[1][4][0] << std::endl;


    return 0;
}