#include "Vector.h"             // inkludera din headerfil här
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <typeinfo>

#include <array>

int main()
{
	
	
	std::cout << "CHKECLEH \n";
	Vector<double> anotherTest {10,20,30,40};
	
	std::cout << anotherTest.size() << "should be 4\n";
	
	for(auto &elt:anotherTest)std::cout<<elt<<", ";
	std::cout << "\n";
	
	

	Vector<int> sderp(1024);
	std::cout << sderp.size() << "\n";
	
	
    Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
    
    Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut så här
    delete [] a;
    
    
	/*
	std::cout << forEachTest.size() << "     ughguhguh \n";
	forEachTest.erase(15);
	
	std::cout << forEachTest.size() << "\n";
	forEachTest.insert(10,0.005);
	
	std::cout << forEachTest.size() << "\n";
	forEachTest.insert(10,0.0044);
	
	std::cout << forEachTest.size() << "\n";
	forEachTest.insert(10,0.0054);
	forEachTest.sort(false);
	for(auto &elt:forEachTest){
		std::cout << elt <<", ";
	}
	
	std::cout <<"\n";
	std::cout << forEachTest.size() << "\n";
	
	forEachTest.reset();
	
	for(auto &elt:forEachTest){
		std::cout << elt <<", ";
	}
	std::size_t testSize = forEachTest.capacity();
	std::cout<< testSize << "capa \n";
	*/
	//double * target = forEachTest.find(20);
	//double tempValue = *target;
	//std::cout << tempValue << "\n";
	
    assert(v.size() == 0);      // tom från början
     
    v.push_back(3.14);          // lägg till ett element sist 
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    
    v.insert(0, 2.10);          // lägg till före element 0, dvs först
    
    
    assert(v[0] == 2.10 &&      // hamnade de rätt?
	
	   v[1] == 3.14);       
    
    assert(v.size() == 2);      // nu ligger två element i vektorn
    
    v.sort(false);              // sortera i fallande ordning
    assert(v[0] == 3.14 &&      // hamnade de rätt?
	   v[1] == 2.10);       
    
    assert(v.size() == 2);      // ingenting ändrat?
    v[1] = 2.11;                // tilldelning av enstaka element;
	
    const Vector<double> &vc = v;  // skapa konstant referens
    assert(vc.size() == 2);     // ok: ändrar ej vektorn som är konstant
    assert(vc[0] == 3.14 &&     // ok: ändrar ej vektorn som är konstant
	   vc[1] == 2.11);
    
    v.erase(0);                 // ta bort första elementet               
    assert(v.size() == 1);      // rätt antal elelment
    
    v.clear();                  // töm hela vektorn
    assert(v.size() == 0);      // tom när alla element är borttagna
    
    
    // kontrollera att följande rader inte går att kompilera
    //vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
    //Vector<char> c = v;         // fel: tilldelning av olika typer
    
    std::size_t vCapSize = v.capacity();
	std::cout<< vCapSize<<"\n";


	std::cout << "MORE TEST \n\n\n\n";
	Vector<int> uggh = {1, 2, 3, 4, 5};
	uggh.erase(2);
	uggh.erase(2);
	uggh.erase(2);
	std::cout << uggh.size()<<"expct 2"<<"\n";
	uggh.insert(1,1);
	std::cout << uggh.size()<<"expct 3"<<"\n";
	
	
	const Vector<int> dddderp(4,2);
	std::cout << dddderp.size()<<" expect 4"<<"\n";
	const Vector<int> dsddderp(1024);
	std::cout << dsddderp.size()<<" expect 1024\n";
	
	Vector<int> uhuhuh = Vector<int>(20);
	std::cout << uhuhuh.size()<<" expect 20\n";
	
	Vector<int> uhuhuhs = (Vector<int>)22;
	std::cout << uhuhuhs.size()<<"expect 22 \n";
	
	
	Vector<int> de;
	std::cout << de.size() << " expect 0\n";

	Vector<int> ded(0);
	std::cout << ded.size() << " expect 0\n";

//init
	Vector<int> derp(20,42);
	std::cout << derp.size() << " : 20 \n";
	Vector<int> burp = derp;//init copy assign
	std::cout << derp.size() << " : 20 \n";
	std::cout << burp.size() << " : 20 \n";
	
	Vector<int> lerp(derp);
	std::cout << "\n" <<derp.size() << " 20 \n";
	std::cout << "\n" <<lerp.size() << " 20  \n";
	derp = derp;
	std::cout << derp.size() << "stay 20 \n";
	
	Vector<int> kerp = std::move(derp);
	std::cout << "\n" <<kerp.size() << " kerp : 20\n";
	std::cout << "\n" <<derp.size() << " derp : 0 \n";
	kerp[0] = 29;
	std::cout << "\n" <<kerp.size() << " kerp : 20\n";
	std::cout << "\n" <<derp.size() << " derp : 0 \n";
	kerp.insert(2,39);
	std::cout << "\n" <<kerp.size() << " kerp : 21\n";
	std::cout << "\n" <<derp.size() << " derp : 0 \n";
	derp = std::move(kerp);
	std::cout << "\n" <<kerp.size() << " kerp : 0\n";
	std::cout << "\n" <<derp.size() << " derp : 21 \n";
	for(auto &elt:kerp){
		std::cout <<elt << "hould not reach here, \n";
	}


	derp[0] = 1;
	derp[1] = 2;
	derp[2] = 3;
	derp.insert(20,200);
	derp.insert(0,100);
	for(auto &elt:derp){
		std::cout << elt <<", ";
	}
	std::cout <<"\n";
	std::cout << "\n" <<derp.size() << " derp : 23 \n";
	std::cout <<"what gets triggerd \n";
	derp = {12,23,32,21};
    
    std::cout << "\n" <<derp.size() << " derp : 4 \n";
	derp.clear();
	
    std::cout << "\n" <<derp.capacity() << " capacity \n";
    std::cout << "\n" <<derp.size() << " derp : 0 \n";
	for(int i = 1; i < 251; i++){
		derp.insert(0,i);
		derp.push_back(20);
	}
	std::cout << "\n" <<derp.size() << " derp : 500 \n";
	
	Vector<int> speed(10);
	speed.insert(0,23);
	std::cout << speed[0] <<"\n";
	speed.erase(5);
	std::cout << "\n" <<speed.size() << " speed : 10 \n";
	
	Vector<float> blublubb(1024);
	std::cout << blublubb.size()<<"\n";
	
	
	
	
	Vector<double> forEachTest(100);
	for(int i = 0; i < 140; i++){
		//forEachTest.insert(forEachTest.size(),i);
		forEachTest.push_back((double) i);
	}
	
	for(int i = 20; i < 40; i++){
		forEachTest[i] = 40;
	}
	std::cout <<"\n" <<forEachTest.size() <<" expct 240\n";
	
	for(int i = 0; i < 140; i++){
		//forEachTest.insert(forEachTest.size(),i);
		forEachTest.insert(forEachTest.size(),(double) i);
	}
	
	
	forEachTest.insert(200,1111);
	forEachTest.erase(250);
	
	
	for(auto &elt:forEachTest){
		std::cout << elt <<", ";//Valgrind error pga default värden
	}
	std::cout <<"\n" <<forEachTest.size() <<" expct 380\n";
	
	Vector<double> varDerp(10);
	varDerp.insert(0,10);
	for(auto &elt:varDerp){
		std::cout << elt <<", ";
	}
	std::cout <<"\n"<< varDerp.size()<<"\n";
	
    return 0;
    
}
