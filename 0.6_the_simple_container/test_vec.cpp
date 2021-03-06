#include <iostream>
#include <stdexcept>
#include "UIntVector.h"     // inkludera din headerfil h�r

int main()
{
    // N�gra saker som ska fungera:
    /*
    UIntVector a(7);           // initiering med 7 element
    a[3] = 9;
    UIntVector b(a);           // kopieringskonstruktor 
    UIntVector c = a;          // kopieringskonstruktor 
	std::cout<<"Assignment \n";
	a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element
    
    const UIntVector e(10);    // konstant objekt med 10 element

	
    int i = e[5];          // const int oper[](int) const k�rs
    i = a[0];              // vektorn �r nollindexerad
    i = a[5];              // int oper[](int) k�rs
    
    a[5]++;                // �ka v�rdet till 8
	
    try {
        i = e[10];             // f�rs�ker h�mta element som ligger utanf�r e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
        std::cout <<"throwing correctly\n";
    }
    std::cout << i <<"\n";
	
    // Diverse saker att testa
    //e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    std::cout<< b[3]<<"\n";
    b = b;                 // hmm: se till att inte minnet som skall beh�llas frig�rs
    std::cout<< b[3]<<"\n";	
    std::cout<<"bluh\n"; //FLYTTAR INTE ORDENLIGT... :/
    */
    UIntVector o(10),l;
    
    l = std::move(o);
	std::cout << o.size()<<"\n";
	std::cout << l.size()<<"\n";
	
	l = std::move(l);
    std::cout << l.size()<<"\n";
	
    return 0;
}
