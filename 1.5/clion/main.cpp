#include <iostream>
#include "Vector.h"
/*
bool operator<(const Vector<bool>::bool_unsigProxy& p1, const Vector<bool>::bool_unsigProxy& p2) {
    bool temp1 = p1;
    bool temp2 = p2;
    if (temp1==true){
        return false;
    }
    if(temp2 == false){
        return false;
    }
    return true;
}*/
int main(){
	Vector<bool> constBool = {false, false, true, false, true};
	std::cout<<"test\n";
    constBool[0] = true;
    std::cout<< constBool[0] << std::endl;

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
	//boolVecto.constFun();
	//const Vector<bool> & dummy = boolVecto;
	//dummy.constFun();
	//const_cast<Vector<bool>&>(dummy).normalFun();
	//Vector<bool> & dummy_2 = const_cast<Vector<bool>&>(dummy);
	//dummy_2.normalFun();
	auto burp = boolVecto.begin();
	auto purb = boolVecto.end();
    burp.getIndex();
    purb.getIndex();
    std::cout << (burp - purb) << "difference \n";


    boolVecto[1] = false;
	std::cout << *burp << " expect 1\n";
	burp += 1;
    burp.getIndex();
    std::cout << " nneP 1 \n";
    std::cout << (purb - burp) << "difference \n";
    std::cout << *burp << " expect 0\n";
	std::cout << boolVecto[1] << " expect 0 \n";
	burp = true;
	++burp;
    burp.getIndex();
    std::cout << " nneP 2 \n";
	--burp;
    burp.getIndex();
    std::cout << " nneP 1 \n";
	burp++;
    burp.getIndex();

    std::cout << " nneP 2 \n";
	burp--;
    burp.getIndex();

    std::cout << " nneP 1 \n";
	std::cout << *burp << " expect 1\n";
	std::cout << boolVecto[1] << " expect 1 \n";
	burp += 4;
    burp.getIndex();
    std::cout << " nneP 5 \n";
    std::cout << (purb - burp) << "difference \n";
    std::cout << (purb == burp) << " expect true \n";
    burp -= 5;
    burp.getIndex();
    std::cout << " nneP 0 \n";


	std::cout << (burp == purb) << " expect false \n";

    burp.getIndex();
    std::cout << " nneP 0 \n";
	auto another = burp+5;
    burp.getIndex();
    std::cout << " nneP 0 \n";
	std::cout << (another == purb) << " expect true \n";
	burp++;
    burp.getIndex();
    purb.getIndex();
	std::cout << (std::distance(burp,purb)) << " expect 4\n";
	//boolVecto.printData();
	for(std::size_t i = 0; i < 40; i++){
		boolVecto.push_back(true);
	}
	//boolVecto.printData();
	purb.getIndex();
	std::cout << *purb << " out of range\n";
	
    std::cout << "BEGINNING WITH KNOWN \n";
    Vector<bool> known = {false, true, true, false, true};
    ///0 2 4 0 16 = 22
	Vector<bool> emptyVector;
	known.printData();
	std::cout << "expect 22\n";
	
	auto start = known.begin();
	
	std::advance(start,1);
	start.getIndex();
    ///1 + 2 + 0 + 8 = 11

	std::copy(start,known.end(),std::back_inserter(emptyVector));
	emptyVector.printData();
	std::cout << "expect 11\n";


    auto knownBegin = known.begin();

    known.printData();
    std::cout << "expect 22\n";
    std::swap(*start,*knownBegin);
    //1 0 4 0 16
    known.printData();
    std::cout << " expect 21 \n";

    std::cout<<"clean clean clean\n\n\n";
    Vector<bool> nextTest = {true, false,true,true,true};

    auto firstNextTest = nextTest.begin();
    Vector<bool>::iterator secondNextTest = firstNextTest +2;
    //auto secondNextTest = firstNextTest +1; //SecondNextTest blir skapat som en const_iterator måste man skriva över allt?
    //secondNextTest++;
    std::advance(secondNextTest,-1);

    std::cout << (firstNextTest < secondNextTest) << " compare Iterator 1\n";
    std::cout << (*firstNextTest)<<" - " << *secondNextTest << "  \n";
    std::cout << (*firstNextTest < *secondNextTest) << "  compareTest 0\n";
/*
    std::cout << "FP INDEX ";
    firstNextTest.getIndex();
    std::cout << "With value " << *firstNextTest << "\n";
    std::cout << "SP INDEX ";
    secondNextTest.getIndex();
    std::cout << "With value " << *secondNextTest<< "\n";

    std::swap(firstNextTest,secondNextTest);


    std::cout << "FP INDEX ";
    firstNextTest.getIndex();
    std::cout << "With value " << *firstNextTest << "\n";
    std::cout << "SP INDEX ";
    secondNextTest.getIndex();
    std::cout << "With value " << *secondNextTest<< "\n";




    std::cout << "SWAPPING VALUES \n";

    std::cout << "FP INDEX ";
    firstNextTest.getIndex();
    std::cout << "With value " << *firstNextTest << "\n";
    std::cout << "SP INDEX ";
    secondNextTest.getIndex();
    std::cout << "With value " << *secondNextTest<< "\n";
    std::swap(*firstNextTest,*secondNextTest);

    std::cout << "FP INDEX ";
    firstNextTest.getIndex();
    std::cout << "With value " << *firstNextTest << "\n";
    std::cout << "SP INDEX ";
    secondNextTest.getIndex();
    std::cout << "With value " << *secondNextTest<< "\n";*/





//Only setting stuff to false, never setting to true
    //Suspect:: missing member function which transfer from lower to higher
    Vector<bool> sortingTest = {true,true};
    for(int i = 1; i < 33 ; i++){
        sortingTest.push_back(false);
    }
    // 0 0 4 +8 +16
    sortingTest.printData();
    //0+2
	std::sort(sortingTest.begin(),sortingTest.end()-10);
    //1+0
    sortingTest.printData();

    /*
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
	//std::swap(sT1,sT2);
	//std::cout<< *sT1 << " "<< *sT2 << "\n";
	
	//std::sort(sT1,sT2);
	

	*/
	
	return 0;


	
}
