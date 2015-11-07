#include <iostream>
#include <cstring>
#include <stdexcept> 
#include <algorithm> 
#include <initializer_list>
#include <type_traits>
#include <iterator>
#ifndef SUPERARRAY
#define SUPERARRAY


template <class T> 
class Vector {
    private:
        std::size_t _totSize;
        std::size_t _nActiveE;
        const static std::size_t init_size = 32; //init size
        const static int size_incr_fct = 2;   //Multi inc size
        T *_dataArray;
        void checkType();
    
    public:
        typedef T* iterator; 
        explicit Vector(); //def init
        ~Vector(); //destruct
        Vector(const Vector &); //copy
        Vector(Vector &&) noexcept; //move
        Vector<T>& operator=(Vector<T> && sA); //move assign
        Vector<T>& operator=(Vector<T> const& sA); //Assigncopy
        explicit Vector(const std::size_t &);
        Vector(const std::size_t &,const T &); //15h senare, får en vara epx
        Vector(const std::initializer_list<T> &);
        //Vector(int s);

        const T operator[](const std::size_t i) const;
        T & operator[](const std::size_t i) ;
        std::size_t size()const;
        void push_back(const T & element);
        void insert(const std::size_t &,const T &);
        void sort(bool);
        void erase(const std::size_t &);
        void clear();
        std::size_t capacity() const;
        const T* begin() const;
        T* begin();
        const T* end() const;
        T* end();
        T* find(T const & target);
        const T* find(T const & target) const;
        void reset();
};

//Initlist
template <class T>
Vector<T>::Vector(const std::initializer_list<T> & bigData){
	//std::cout << "initlist trigger \n";
    _totSize = bigData.size();
    _nActiveE = bigData.size();
    _dataArray = new T [_totSize];
    std::size_t i = 0;
    for(auto &elt : bigData){
		_dataArray[i] = elt;
		i++;
	}
	
}





template <class T>
Vector<T>::Vector(const std::size_t & reqSize){
    checkType();
    _dataArray = new T[reqSize];
    _totSize = reqSize;
    _nActiveE = reqSize;
    //std::cout << "size init\n";
    
    for(std::size_t i = 0; i < _totSize; i++){
        _dataArray[i] = T {};
    }
}
template <class T>
Vector<T>::Vector(const std::size_t & reqSize,const T & data){
    checkType();
    _dataArray = new T[reqSize];
    _totSize = reqSize;
    _nActiveE = reqSize;
    for(std::size_t i = 0; i < _totSize; i++){
        _dataArray[i] = data;
    }
}

//Default
template <class T> 
Vector<T>::Vector()
    : _totSize(init_size)
    , _nActiveE(0)
    //, _dataArray(new T [init_size])
{
	_dataArray = new T [init_size];
    checkType();
    //_nActiveE=0;
    //_totSize = init_size;
    //_nActiveE = 0;
    //std::cout<<"default constructor"<<"\n";
    //_dataArray = new T [init_size];
}
//Destroy
template <class T> Vector<T>::~Vector(){
    if(_dataArray){
		//std::cout << "destroy trigg\n";
        delete[] _dataArray;
        _dataArray = NULL;}
}
//Copy constructor
template <class T> Vector<T>::Vector(const Vector &ar){
    checkType();
    _totSize = ar._totSize;
    _nActiveE = ar._nActiveE;
    _dataArray = new T [_totSize];
    for(std::size_t i = 0; i < _nActiveE; i++){
		_dataArray[i] = ar._dataArray[i];
	}
	
    //memcpy(_dataArray,ar._dataArray,sizeof(T)*_totSize);
}
//Move
template <class T>
Vector<T>::Vector(Vector &&sA) noexcept
    : _totSize(sA._totSize)
    , _nActiveE(sA._nActiveE)
    , _dataArray(sA._dataArray)
{
    checkType();
    //std::cout<<"MOVING STUFF\n";
    sA._dataArray = nullptr;  
    sA._totSize = 0;
    sA._nActiveE = 0;  
}
//Move assignment
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> && sA){
    if(this==&sA) return *this;
    delete[] _dataArray;
    _dataArray = sA._dataArray;
    _totSize = sA._totSize;
    _nActiveE = sA._nActiveE;
    sA._dataArray = nullptr;
    sA._totSize = 0;
    sA._nActiveE = 0;
    return *this;
}


//Assignment copy via = 
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& sA){
    if(this==&sA) return *this;
    delete[] _dataArray;
    _totSize = sA._totSize;
    _nActiveE = sA._nActiveE;
    _dataArray = new T [_totSize];
    for(std::size_t i = 0; i < sA._nActiveE;i++){
        _dataArray[i] = sA._dataArray[i];
    }
    
    return *this;
}





//get size()
template <class T> 
std::size_t Vector<T>::size() const {
    return _nActiveE;
}

//bracket
template <class T> 
const T Vector<T>::operator[](const size_t i) const{
    //std::cout <<"CONST GET VALUE of ELT\n";
    if(i >= _nActiveE){
        throw std::out_of_range("index not in range");}
    const T value = _dataArray[i];
    return value;
}
        
template <class T>      
T & Vector<T>::operator[](const size_t i) { 
    //std::cout <<"DOING THE [] OPERATOR \n";

    if(i >= _nActiveE){
        throw std::out_of_range("index not in range");}
    return _dataArray[i];
}



//pushback
template <class T>
void Vector<T>::push_back(const T  & element){
    //std::cout << "pushbackar \n";
    _nActiveE++;
    if (_nActiveE > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
        T * tempArray = new T [_totSize];
        for(std::size_t count = 0; count < _nActiveE-1;count++){
			tempArray[count] = _dataArray[count];}
        tempArray[_nActiveE-1] = element;
        delete[] _dataArray;
        _dataArray = tempArray;
        tempArray = nullptr;
    }
    else{
		_dataArray[_nActiveE-1] = element;
	}    
}
//INSERT
template <class T>
void Vector<T>::insert(const std::size_t & i,const T & element){
    if(i > _nActiveE){
        throw std::out_of_range("index not in range");}
    //std::cout << "Insert \n";
    _nActiveE++;
    if(_nActiveE > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
		T * tempArray = new T [_totSize];
		for(std::size_t count = 0; count < i;count++){
			tempArray[count] = _dataArray[count];}
		for(std::size_t count = _nActiveE-1; count > i; count--){
			tempArray[count] = _dataArray[count-1];
		}
		tempArray[i] = element;
		delete[] _dataArray;
		_dataArray = tempArray;
		tempArray = nullptr;    
	}
	else{
		for(std::size_t count = _nActiveE-1; count > i; count--){
			_dataArray[count] = _dataArray[count-1];
		}
		_dataArray[i] = element;
    
    
    
	}
}

//sort
bool myAscScrit (double i,double j) { return (i<j); }
bool myDesScrit (double i,double j) { return (i>j); }

template <class T>
void Vector<T>::sort(bool ascending){
    //Från och med TILL//
    //std::cout << "Sorting\n";
    if (ascending){
        std::sort(_dataArray,_dataArray+_nActiveE,myAscScrit);
    }
    else{
        std::sort(_dataArray,_dataArray+_nActiveE,myDesScrit);
    }
}

//erase
template <class T>
void Vector<T>::erase(const std::size_t & i){
    if(i >= _nActiveE){
        throw std::out_of_range("index not in range");}
    _nActiveE--;
    
    for(std::size_t start = i;start <_nActiveE;start++){
        _dataArray[start] = _dataArray[start+1];
    }
    
    
}

//clear
template <class T>
void Vector<T>::clear(){
    _nActiveE = 0;
}
//capacity
template <class T>
std::size_t Vector<T>::capacity() const{
    return _totSize;
}


//template <class T>
//typename Vector<T>::iterator Vector<T>::begin() const{
//  return const &_dataArray[0];
//}

template <class T>
T* Vector<T>::begin(){
    T* it =  &_dataArray[0];
    return it;
}
template <class T>
const T* Vector<T>::begin() const{
    const T* it =  &_dataArray[0];
    return it;
}

template <class T>
T* Vector<T>::end(){
    T* it =  &_dataArray[_nActiveE];
    return it;
}

template <class T>
const T* Vector<T>::end() const{
    const T* it =  &_dataArray[_nActiveE];
    return it;
}

template <class T>
T* Vector<T>::find(T const & target){
    for(std::size_t i = 0; i < _nActiveE;i++){
        if(_dataArray[i] == target){
            T* it =  &_dataArray[i];
            return it;
        }
    }
    const typename Vector<T>::iterator it =  &_dataArray[_nActiveE];
    return it;
}

template <class T>
const T* Vector<T>::find(T const & target) const{
    for(std::size_t i = 0; i < _nActiveE;i++){
        if(_dataArray[i] == target){
            const T* it =  &_dataArray[i];
            return it;
        }
    }
    const typename Vector<T>::iterator it =  &_dataArray[_nActiveE];
    return it;
}

template <class T>
void Vector<T>::checkType(){
    static_assert ( std::is_move_assignable<T>::value , "not move assignable" );
    static_assert ( std::is_move_constructible<T>::value , "not move constructible" );
    /*std::cout << "check type \n";
    if(false == std::is_move_assignable<T>::value){
            std::cerr << "Problem..\n";
            throw std::runtime_error("not Assignable");
    }
    if(false == std::is_move_constructible<T>::value){
            std::cerr << "problem....\n";
            throw std::runtime_error("NOT MOVE CONS..");
    }*/
    
}

template <class T>
void Vector<T>::reset(){
    for(std::size_t i = 0; i < _nActiveE;i++){
        _dataArray[i] = T{};  
    }
}

/*
template <class T>
void Vector<T>::clear(){
    delete[] _dataArray;
    _dataArray = new T [init_size];
    _nActiveE = 0;
    _totSize = init_size;
}
*/
#endif
/*
0.1  MAKE IT HAPPEN  
--------------------------------------------------------------------------------
:::: What does `$*` mean inside a makefile?
--------------------------------------------------------------------------------

Answer: For every argument (separated with space) after make, it takes the word and replaces $* for all arguments

--------------------------------------------------------------------------------
:::: What is the purpose of `-Wall` and -g, when passed as arguments to g++?
--------------------------------------------------------------------------------

Answer: -g makes so after compiled it is possible to debug code with gdb, probally at cost of performance
-wall Makes compiler to write stuff in terminal with all potential errors/problems with the code

--------------------------------------------------------------------------------
:::: What is the difference between an object file, and an executable?
--------------------------------------------------------------------------------

Answer: executable contains machine code which can be run where all links and libraries has been packed
, while object file contains information abour object but might not been linked with libraries or other files.

--------------------------------------------------------------------------------





0.2  HELLO WORLD

-----
:: If you invoke touch hello.cpp prior to invoking make;
-How many files were rebuilt
1 file, main.out were rebuilt, hello.o was the same
-Why?
The timestamp on main.cpp changes due to touch, and because of that a "change" could have been happened and it had to be rebuilt
---

Why do you think make checks the modification timestamp....?
To be quick, if there is a very large project and only one small thing changes, 
not everything should be required to be recompiled, only those files being affected. 
Checking timestamp is simpleway to determine if anything could have happened

-------------------------------------------------------------------------------
:::: What is the purpose of `std::cout`, `std::cerr`, and `std::clog`,
     respectively?
-------------------------------------------------------------------------------

Answer: Things written to std::cout writes out to console
std::cerr also write to console but tells it is an error message and might be coloured
std::clog tells the computer to log something, and where it logs depends on computer
-------------------------------------------------------------------------------





0.3  TRAIN SPOTTING

    int powerof (int x, int y) {
      int res = 1;

      for (int i = 0; i < y; ++i);
        res *= x;

      return res;
    }

    int main () {
      int const a = 2;
      int const b = 4;

      int   x = powerof(a, b); 
      float y = 3.1415;

      std::cout << a << "^" << b << " = " << x << ";\n";

      if (y == 3.1415)
        std::cout << y << " is equal to 3.1415!\n";
      else
        std::cout << y << " is not equal to 3.1415!\n";
    }

--------------------------------------------------------------------------------
:::: Why does not `powerof` return the expected value (16), when invoked with 2 and 4?
--------------------------------------------------------------------------------

Answer: the for loop has a ; at the end so the next line is not "looped" 
over and will be "outside of loop" and will only run once, x = 2

--------------------------------------------------------------------------------
:::: Why does not `y` compare equal to 3.1415?
--------------------------------------------------------------------------------

Answer: 3.1415 is converted to a double, and when we compare float to double
their precision is different, so when comverted from float to double some precision
error occures and they differ.


--------------------------------------------------------------------------------
:::: Is there any difference in behavior if we compare `y` to 3.1415f, if so: why?
--------------------------------------------------------------------------------

Answer: We tell that 3.1415f is a float number and then we will compare float with float
which then has same precision

--------------------------------------------------------------------------------
:::: What is the recommended method to use when trying to determine if
:::: two floating-point values are equal, and why?
--------------------------------------------------------------------------------

Answer: Allow a small error when comparing, so we set abs(float_A - float_b)<tolerance

--------------------------------------------------------------------------------


0.4 DOES IT FIT

int count_if_followed_by (char const * p, int len, char a, char b) {
  int        count = 0;
  char const * end = p + len;

  while (p != end) {
    if (*p == a && *(p+1) == b)
      count += 1;

    ++p;
  }

--------------------------------------------------------------------------------
:::: Why is it important to test the boundary conditions of an implementation,
     especially in the case of `count_if_followed_by`?
--------------------------------------------------------------------------------

Answer: Making sure that count_if_followed_by dont check the last element, when last +1 which should not exist	

--------------------------------------------------------------------------------



0.5 WILL IT FLOAT (birth.cpp)

class A {
public:
   A () {
     std::cout << "default-constructor" << std::endl;
   }

   A (A const& src) {
     std::cout << "copy-constructor" << std::endl;
   }

  ~A () {
    std::cout << "destructor" << std::endl;
  }

   A(char const* s) {
      std::cout << "some other constructor" << std::endl;
   }

   A& operator= (A const& src) {
     std::cout << "the assignment operator" << std::endl;
     return *this;
   }
};

void no_ref(A a) {}
void with_ref(const A & a) {}

int main()
{
    A a("my name is a");

    A b = a;          // what is the difference
    A c(a);           // between these three
    A d;              // forms of initialization?

    d = a;

      no_ref (a);     // will this copy the value of `a`?
    with_ref (a);     // will this copy the value of `a`?

    A *aa = new A[5];
    delete aa;        // what will happen?
    return 0;
}

--------------------------------------------------------------------------------
:::: What different constructors are invoked, and when?
--------------------------------------------------------------------------------

Answer: 
A b = a; Triggers the copy constructor
A c(a);  Also triggers the copy constructor
A d;     Default constructor
d = a;   Assignment operation
no_ref = copy, then delete
with_ref = nothing happens
A *aa = new A[5]; create 5 "A" with default constructor
delete aa; Triggers delete constructor

--------------------------------------------------------------------------------
:::: Will there be any temporaries created, if so; when?
--------------------------------------------------------------------------------

Answer: with 
A a("something")
no_ref(a)
created but terminated afterwards

--------------------------------------------------------------------------------
:::: When are the objects destructed, an why?
--------------------------------------------------------------------------------

Answer: delete destroys 

--------------------------------------------------------------------------------
:::: What will happen if we try to free the dynamically allocated
:::: memory through `delete p`, instead of `delete [] p`?

Answer: Behaviour is undefined, depends on compilator

--------------------------------------------------------------------------------


0.5 WILL IT FLOAT (bad_plumming.cpp)

struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++)
        if (v[i] != 0)
            v[i] = new Data;
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    foo(v, size);
}

--------------------------------------------------------------------------------
:::: valgrind indicates that the program suffers from a few problems, which and
:::: why?
--------------------------------------------------------------------------------

Answer (About birth): Dlete doesn't delete correctly as it is not delete[], and what have happened is probablly
delete only removed first element of the array and no pointer long points to the rest and are "lost" or leaked


--------------------------------------------------------------------------------
:::: valgrind indicates that the program suffers from a few problems, which and
:::: why?
--------------------------------------------------------------------------------

Answer (About bad_plumming): Indicates that the program suffer from memory leak
because not all allocated memory was deleted before the program was finished. Need to add delete[] v
at the end

--------------------------------------------------------------------------------
:::: If you comment out the entire if-block in foo, is there any difference in
:::: how much memory that is leaked?
--------------------------------------------------------------------------------

Answer: The amount of memory leaked stayed the same after commenting out, but number
of errors valgrind detected went down from 6 to 1.

--------------------------------------------------------------------------------
:::: Revert bad_plumming.cpp to its original state, and comment out
:::: only the line that contains the if-condition.
::::
:::: If you now change the last line of `main` to the following; why is it
:::: that valgrind still issue diagnostics related to memory management?
::::
:::: Data ** p = foo (v, size);
:::: delete [] p;
--------------------------------------------------------------------------------

Answer: p is not a reference, but another pointer to pointer, so when p is created it copies
values of where v was pointed, then we delete p and v is still in memory

--------------------------------------------------------------------------------



0.6  THE SIMPLE CONTAINER
--------------------------------------------------------------------------------
:::: `operator[]` must in some cases be marked as `const`, but not always; when,
:::: and why?
--------------------------------------------------------------------------------

Answer: when creating new object that is const, then whenever it uses an operator 
it must use the version of operator marked as const. If the operator doesn't have a
const version, then the object cannot use that operator.

--------------------------------------------------------------------------------
:::: The semantics of copying a UIntVector might not be trivial; why must we 
:::: manually implement the relevant code, instead of having the compiler generate
:::: it for us?
--------------------------------------------------------------------------------

Answer: Makes shallow copy, but for dynamic allocated memory the default one will 
end up with copy the adress and not the contents of the adress. So now two UIntVector
share the same memory



--------------------------------------------------------------------------------



0.7  THE TEMPLATE VECTOR
--------------------------------------------------------------------------------
:::: Iterating over a range of elements can be done with a range-based for-loop,
:::: but the type of `source` must meet certain requirements; what are they?
--------------------------------------------------------------------------------

Answer: source must have a method which has iterator "pointer" that shows where the beginning and end is, and must also support operator++ (check next element) !=, compare the iterator,

--------------------------------------------------------------------------------
:::: The C++ Standard sometimes state that a type in the Standard Library is
:::: "unspecified"; why do you think that is?
--------------------------------------------------------------------------------

Answer: I think it is because it is not important what the type is, as long as whatever
it returns, it fulfills some critera, like the begin(), must return something that can be 
compared with pointer of same type and other criteria. (as long as it support some set of operators).

--------------------------------------------------------------------------------
*/


