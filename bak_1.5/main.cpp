#include <iostream>
#include "Vector.h"



int main(){
	const Vector<bool> constBool = {true, false, true, false, true};
	std::cout << "Beginning with iterator test assuming constBoll[0] = 1\n";
	//auto derp = constBool.begin();
	Vector<bool>::const_iterator derp = constBool.begin();
	std::cout << *derp << " expect 1\n";
	derp += 1;
	std::cout << *derp << " expect 0\n";
	
	/*
    Vector<bool> boolVecto = {true, false, true, false, true};
	auto burp = boolVecto.begin();
	auto purb = boolVecto.end();
	boolVecto[1] = false;
	std::cout << *burp << " expect 1\n";
	burp += 1;
	std::cout << *burp << " expect 0\n";
	std::cout << boolVecto[1] << " expect 0 \n";
	burp += 4;
	std::cout << (burp == purb) << " expect true \n";
	//std::cout << *burp << " out of range\n";
	return 0;
	* */
}
