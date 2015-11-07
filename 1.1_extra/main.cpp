//#include "Matrix.h"
#include "Matrix.h"
#include <iostream>
#include <stdexcept>

int main(){
	std::cout << "test \n";
	Matrix derp(2,2);
	std::cout << "exit\n";
	derp[0][0] = 11;
	derp[0][1] = 12;
	derp[1][0] = 21;
	derp[1][1] = 22;
	Matrix serp(derp);
	
	Matrix burp(2,2);
	burp[0][0] = 33;
	burp[0][1] = 34;
	burp[1][0] = 43;
	burp[1][1] = 44;
	
	Matrix murp = derp*2;
	std::cout << "**********\n";
	//Matrix kurp = 2*derp;
	std::cout << derp << " expect 11 12 ; 21 22\n";
	derp = derp+burp;
	
	int value = serp[1][1];
	std::string test;
	std::cout << value << "expect 22\n";
	std::cout << derp << " expect 44 46; 64 66 \n";
	std::cout << burp << " expect 33 34; 43 44\n";
	std::cout << murp << " expect 22 24; 42 44 \n";
	//std::cout << kurp << " expect 22 24; 42 44\n";
	
	
	/* //istream test
	std::cin >> derp;	
	std::cout << "\n***********\n\n";
	std::cout << derp <<"\n";
	* */
	
	Matrix mew(2,2);
	Matrix kew(2,2);
	mew[0][0] = 1;
	mew[0][1] = 2;
	mew[1][0] = 3;
	mew[1][1] = 4;
	kew[0][0] = 5;
	kew[0][1] = 6;
	kew[1][0] = 7;
	kew[1][1] = 8;
	
	std::cout << mew << " expct 1 2; 3 4\n";
	std::cout << kew << " expct 5 6; 7 8 \n";
	std::cout << mew*mew <<" expct 7 10; 15 22\n";
	std::cout << mew*kew <<" expct 19 22; 43 50  \n";
	
	std::cout << kew*mew <<"  expct 23 34; 31 46 \n";
	std::cout << kew-mew << " expect 4 4 ; 4 4\n";
	std::cout << mew.transpose() << "1 3; 2 4 \n";
	std::cout << mew << " 1 3 2 4\n";
	
	std::cout << -mew <<" -1 -3 ; -2 -4\n";
	
	std::cout << mew*5 << "\n";
	std::cout << mew[0][0] << "\n";
	
	std::cout << 5*mew << "\n";
	mew += mew;
	std::cout << mew << "\n";
	mew *= mew;
	std::cout << mew << "\n";
	std::cout << mew.norm() << "\n";
}
