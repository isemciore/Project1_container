#include <iostream>
#include <assert.h>
#include "Vector.h"

struct T1{
    int id = 20;
    T1() {++ object_count;}
    T1(int sum) {++ object_count;id = sum;}
    T1(T1 const& src) {++object_count;id = src.id;}
    ~T1() {--object_count;}
    static unsigned int object_count;
};

unsigned int T1::object_count = 0;

int main(){

    /*
    T1 (**tier1ptr);

    tier1ptr = new T1*[2];
    tier1ptr[0] = new T1{};
    tier1ptr[1] = new T1{};

    T1 **tier2ptr = new T1*[2];
    tier2ptr[0] = tier1ptr[0];
    tier2ptr[1] = tier1ptr[1];
    delete tier1ptr;
    tier1ptr = tier2ptr;
    delete tier1ptr[0];
    delete tier1ptr[1];

    delete[] tier2ptr;
    */
///////////////////

    Vector<T1> v2 (3);

    assert(T1::object_count == 3);
    v2.erase(2);
    assert(T1::object_count == 2);
    v2.push_back(T1{});
    assert(T1::object_count == 3);
    v2.erase(2);
    assert(T1::object_count == 2);
    v2.push_back(T1{});
    assert(T1::object_count == 3);

    v2.insert(1,T1{});
    assert(T1::object_count == 4);

    v2.erase(3);
    assert(T1::object_count == 3);
    v2.erase(1);
    assert(T1::object_count == 2);
    v2.erase(0);
    assert(T1::object_count == 1);
    v2.insert(0,T1{});
    assert(T1::object_count == 2);

    int randNum;

    for(int i = 0; i < 1000; i++){
        randNum = rand()%(i+1);
        v2.insert(randNum,T1{});
        assert(T1::object_count == (2+1+i));
    }
    v2.push_back(T1{});

    Vector<T1> vCopy(v2);
    vCopy.clear();
    vCopy = v2;
    srand(12121);
    for(int i = 1003; i > 0; i--){ //1003 elements then erase 1
        randNum = rand()%(i); //as erase 0 is erasing true 1
        v2.erase(randNum);
        assert(T1::object_count == (1003+i-1));
    }

    vCopy.erase(1002);
    for(int i = 1002; i > 500; i--){ //1003 elements then erase 1
        randNum = rand()%(i); //as erase 0 is erasing true 1
        vCopy.erase(randNum);
        assert(T1::object_count == (i-1));
    }
    for(int i = 500; i > 0; i--){ //1003 elements then erase 1
        randNum = rand()%(i); //as erase 0 is erasing true 1
        vCopy.erase(0);
        assert(T1::object_count == (i-1));
    }




    Vector<T1> anotherVector;
    for(int i = 1; i <= 1000; i++){
        anotherVector.push_back(T1{});
        assert(T1::object_count == (i));
    }
    for(int i = 1000; i > 0; i--){ //1003 elements then erase 1
        assert(T1::object_count == (i));
        randNum = rand()%(i); //as erase 0 is erasing true 1
        anotherVector.erase(randNum);
    }
    assert(T1::object_count == 0);


    Vector<T1> anvec;
    for(int i = 40; i >= 0;i--){
        anvec.insert(0,T1(i));
    }

    for(int i = 0; i <=40;i++){
        assert(anvec[i].id ==i);
    }

    Vector<T1> burp = anvec;


    assert(T1::object_count == 82);

    Vector<T1> derp(5);
    assert(T1::object_count == 87);
    derp = burp;
    assert(T1::object_count == 123);
    Vector<T1> lerp(5);
    assert(T1::object_count == 128);
    derp = lerp;
    assert(T1::object_count == 92);
    Vector<T1> listinit = {T1(5),T1(5),T1(5),T1(5),T1(5),T1(5)};
    assert(T1::object_count == 98);
    Vector<T1> sizevect(5,T1{});
    assert(T1::object_count == 103);
    listinit = sizevect;
    assert(T1::object_count == 102);


    burp = std::move(listinit);
    std::cout << T1::object_count << "\n";
    assert(T1::object_count == 61);

    Vector<T1> movedto = std::move(burp);
    assert(T1::object_count == 61);
    assert(burp.size() == 0);

}