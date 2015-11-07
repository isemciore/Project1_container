#include <iostream>
#include <assert.h>
#include "Vector.h"

struct T1{
    T1() {++ object_count;}
    T1(T1 const&) {++object_count;}
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


    const Vector<T1> v1(1024);
    Vector<T1>::const_iterator derp = v1.begin();

    (*derp).~T1();
    Vector<T1>::const_iterator burp = v1.end();
    for(auto elt:v1){
    }

    Vector<T1> v3(1024);
    v3.erase(0);
    return 0;
}