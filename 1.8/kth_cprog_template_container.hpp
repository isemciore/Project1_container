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
    
    T * temp_array = new T[ar._totSize];
    try{
		for(std::size_t i = 0; i < ar._nActiveE;i++){
			temp_array[i] = ar._dataArray[i];
		}
	}catch(...){
		delete[] temp_array;
		throw;
	}
    _dataArray = temp_array;
    _totSize = ar._totSize;
    _nActiveE = ar._nActiveE;
    temp_array = nullptr;
    
    
    //for(std::size_t i = 0; i < _nActiveE; i++){
	//	_dataArray[i] = ar._dataArray[i];
	//}
	
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
    
    T * temp_array = new T[sA._totSize];
	try{
		for(std::size_t i = 0; i < sA._nActiveE;i++){
			temp_array[i] = sA._dataArray[i];
		}
	} catch(...){
		delete[] temp_array;
		throw;
	}
    delete[] _dataArray;
    _dataArray = temp_array;
    _totSize = sA._totSize;
    _nActiveE = sA._nActiveE;
    temp_array = nullptr;
    
    
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
   
    if(_nActiveE+1 > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
		T * tempArray = new T [_totSize];
		
		try{
			for(std::size_t count = 0; count < i;count++){
				tempArray[count] = _dataArray[count];}
			for(std::size_t count = _nActiveE; count > i; count--){
				tempArray[count] = _dataArray[count-1];
			}
			tempArray[i] = element;
		} catch(...){
			delete[] tempArray;
			throw;
		}
		delete[] _dataArray;
		_dataArray = tempArray;
		tempArray = nullptr;  
		_nActiveE++;  
	}
	else{
		T * tempArray = new T[_totSize];
		try{
			for(std::size_t count = 0; count < i; count ++){
				tempArray[count] = _dataArray[count];
			}
			tempArray[i] = element;
			for(std::size_t count = _nActiveE; count > i; count--){
				tempArray[count] = _dataArray[count-1];
			}
		} catch(...){
			delete[] tempArray;
			throw;
		}
		delete[] _dataArray;
		_dataArray = tempArray;
		_nActiveE++;
		tempArray = nullptr;
    
    
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
    T * tempArray = new T[_totSize];
    try{
		for(std::size_t start = 0; start < i;start++){
			tempArray[start] = _dataArray[start];
		}
		for(std::size_t index = i; index < _nActiveE-1; index++){
			tempArray[index] = _dataArray[index+1];
		}
	} catch(...){
		delete[] tempArray;
		throw;
	}
    delete[] _dataArray;
    _dataArray = tempArray;
    tempArray = nullptr;
    _nActiveE--;
    
    
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
