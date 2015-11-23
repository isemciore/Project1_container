#include <iostream>
#include "Vector.h"



int main(){
	std::cout << "test \n";
	unsigned int test = 0;
	std::cout << test-1 << "\n";
	Vector<bool> boolV_1;
	Vector<bool> boolV_2(4);
	
	std::size_t valu_1 = 299;
	unsigned int valu_2 = 32;
	std::cout << valu_2 << "\n";
	//or operation, 1u<<31
	//Ändrar bit vid index 31, 1u<<2 = 0...00100 or med värde
	valu_2 |= (1u << 31);
	std::cout << valu_2 << "\n";
	std::cout << valu_1/valu_2 << "\n";
	std::cout << 1u <<" : 1u \n";
	std::cout << (1u<<0) << "\n";
	std::cout << (1u<<1) << "\n";
	std::cout << (1u<<2) << "\n";
	
	unsigned int valu_3 = (13);
	std::cout << valu_3 << "\n";
	
	std::cout << (valu_3>>2) << "\n";
	valu_3 = (valu_3 >> 2);
	std::cout << valu_3%2 << "\n";
	std::cout << "*****\n";
	Vector<bool> boolV3(5);
	boolV3[2] = true;
	std::cout << "*****\n";
	bool temp = boolV3[2];
	std::cout << temp << " expt 1\n";
	std::cout << boolV3[2] << " expt 1\n";
	std::cout << boolV3[1] << " expt rnd (0 or 1)\n";
	
	const Vector<bool> dconstBool(3,1);
	std::cout << dconstBool[0] << "\n";
	std::cout << dconstBool[1] << "\n";
	std::cout << dconstBool[2] << "\n";
	const Vector<bool> constBool = {true, false, true, false, true};
	std::cout << "Beginning with iterator test assuming constBoll[0] = 1\n";
	auto derp = constBool.begin();
	std::cout << *derp << " expect 1\n";
	derp += 1;
	std::cout << *derp << " expect 0\n";
	
	
	return 0;
}
