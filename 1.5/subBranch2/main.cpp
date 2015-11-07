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
	
	Vector<bool> largerSize(40);
	for(std::size_t i = 0; i < 40; i++){
		largerSize[i] = true;
	}
	
	//largerSize.printData();
	
	
    Vector<bool> boolVecto = {true, true, false, false, true};
	boolVecto.constFun();
	const Vector<bool> & dummy = boolVecto;
	dummy.constFun();
	const_cast<Vector<bool>&>(dummy).normalFun();
	Vector<bool> & dummy_2 = const_cast<Vector<bool>&>(dummy);
	dummy_2.normalFun();
	auto burp = boolVecto.begin();
	auto purb = boolVecto.end();
	boolVecto[1] = false;
	std::cout << *burp << " expect 1\n";
	burp += 1;
	std::cout << *burp << " expect 0\n";
	std::cout << boolVecto[1] << " expect 0 \n";
	burp = true;
	++burp;
	--burp;
	burp++;
	burp--;
	std::cout << *burp << " expect 1\n";
	std::cout << boolVecto[1] << " expect 1 \n";
	burp += 4;
	std::cout << (burp == purb) << " expect true \n";
	burp -= 5;
	std::cout << (burp == purb) << " expect false \n";
	auto another = burp+5;
	std::cout << (another == purb) << " expect true \n";
	burp++;
	std::cout << (std::distance(burp,purb)) << " expect 4\n";
	//boolVecto.printData();
	for(std::size_t i = 0; i < 40; i++){
		boolVecto.push_back(true);
	}
	//boolVecto.printData();
	
	std::cout << *burp << " out of range\n";
	
	
    Vector<bool> known = {false, false, true, true, true};
    ///0+0+4+8+16
	Vector<bool> emptyVector;
	//known.printData();
	std::cout << "expect 28\n";
	
	auto start = known.begin();
	
	std::advance(start,1);
	///0+2+4+8
	
	std::copy(start,known.end(),std::back_inserter(emptyVector));
	//emptyVector.printData();
	
	std::cout << "expect 14\n";
	//std::sort(emptyVector.begin(),emptyVector.end());
	
	Vector<bool>::iterator known_begin = known.begin();
	Vector<bool>::iterator known_end   = known.end();
	known_end--;
	
	Vector<bool> poke = known;
	known = poke; 

	poke.printData();
	auto test_pointer = poke.begin();
	*test_pointer = true;
	poke.printData();
	
	Vector<bool> swapTest = {false ,true, false, true};
	Vector<bool>::iterator sT1 = swapTest.begin();
	Vector<bool>::iterator sT2 = swapTest.begin();
	++sT2;
	std::cout<< *sT1 << " "<< *sT2 << "\n";
	std::swap(sT1,sT2);
	//std::cout<< *sT1 << " "<< *sT2 << "\n";
	
	//std::sort(sT1,sT2);
	

	
	
	return 0;
	
}
