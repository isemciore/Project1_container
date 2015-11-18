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
        std::allocator<T> mem_type_allocator;
        T *_dataArray;
        void checkType();
    
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        Vector(); //def init
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

//Default
template <class T>
Vector<T>::Vector()
        : _totSize(init_size)
        , _nActiveE(0)
//, _dataArray(new T [init_size])
{
    _dataArray = mem_type_allocator.allocate(_totSize);
    checkType();
    //_nActiveE=0;
    //_totSize = init_size;
    //_nActiveE = 0;
    //std::cout<<"default constructor"<<"\n";
    //_dataArray = new T [init_size];
}




//Initlist
template <class T>
Vector<T>::Vector(const std::initializer_list<T> & bigData){
	//std::cout << "initlist trigger \n";
    _totSize = bigData.size();
    _nActiveE = bigData.size();
    _dataArray = mem_type_allocator.allocate(_totSize);

    std::size_t i = 0;
    for(auto &elt : bigData){
        mem_type_allocator.construct(_dataArray+i,elt);
		i++;
	}

}
template <class T>
Vector<T>::Vector(const std::size_t & reqSize){
    checkType();
    _dataArray = mem_type_allocator.allocate(reqSize);
    _totSize = reqSize;
    _nActiveE = reqSize;
    //std::cout << "size init\n";
    for(std::size_t i = 0; i < _totSize; i++){
        mem_type_allocator.construct(_dataArray+i);
        //_dataArray[i] = T {};
    }
}

template <class T>
Vector<T>::Vector(const std::size_t & reqSize,const T & data){
    checkType();
    _dataArray = mem_type_allocator.allocate(reqSize);
    //_dataArray = new T[reqSize];
    _totSize = reqSize;
    _nActiveE = reqSize;
    for(std::size_t i = 0; i < _totSize; i++){
        mem_type_allocator.construct(_dataArray+i,data);
        //_dataArray[i] = data;
    }
}
//Destroy
template <class T> Vector<T>::~Vector(){
    if(_dataArray){
		//std::cout << "destroy trigg\n";
        //delete[] _dataArray;
        //_dataArray = NULL;
        for(int i = 0; i < _nActiveE;i++) {
            mem_type_allocator.destroy(_dataArray+i);
        }
        mem_type_allocator.deallocate(_dataArray,sizeof(T));
    }
}
//Copy constructor
template <class T> Vector<T>::Vector(const Vector &ar){
    checkType();
    _totSize = ar._totSize;
    _nActiveE = ar._nActiveE;
    _dataArray = mem_type_allocator.allocate(_totSize);
    //_dataArray = new T [_totSize];
    for(std::size_t i = 0; i < _nActiveE; i++){
		mem_type_allocator.construct(_dataArray+i,ar._dataArray[i]);
        //_dataArray[i] = ar._dataArray[i];
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
    for(int i = 0; i < _nActiveE;i++){
        mem_type_allocator.destroy(_dataArray+i);
    }
    mem_type_allocator.deallocate(_dataArray,sizeof(T));
    //delete[] _dataArray;
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
    for(int i = 0; i<_nActiveE;i++) {
        mem_type_allocator.destroy(_dataArray+i);
    }
    mem_type_allocator.deallocate(_dataArray,sizeof(T));
    //delete[] _dataArray;
    _totSize = sA._totSize;
    _nActiveE = sA._nActiveE;

    _dataArray = mem_type_allocator.allocate(_totSize);
    //_dataArray = new T [_totSize];
    for(std::size_t i = 0; i < sA._nActiveE;i++){
        mem_type_allocator.construct(_dataArray+i,sA._dataArray[i]);
        //_dataArray[i] = sA._dataArray[i];
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
    //this->insert(_nActiveE,element);

    //std::cout << "pushbackar \n";
    _nActiveE++;
    if (_nActiveE > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
        T* tempArray = mem_type_allocator.allocate(_totSize);
        //T * tempArray = new T [_totSize];
        for(std::size_t count = 0; count < _nActiveE-1;count++) {
            mem_type_allocator.construct(tempArray+count,_dataArray[count]);
            mem_type_allocator.destroy(_dataArray+count);
            //tempArray[count] = std::move(_dataArray[count]);
            //tempArray[count] = _dataArray[count];
        }
        mem_type_allocator.construct(tempArray+(_nActiveE-1),element);
        //tempArray[_nActiveE-1] = element;
        mem_type_allocator.deallocate(_dataArray,sizeof(T));
        _dataArray = nullptr;
        //delete[] _dataArray;
        _dataArray = tempArray;
        tempArray = nullptr;
    }
    else{
        mem_type_allocator.construct(_dataArray+(_nActiveE-1),element);
		//_dataArray[_nActiveE-1] = element;
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
		T* tempArray = mem_type_allocator.allocate(_totSize);
        //T * tempArray = new T [_totSize];
		for(std::size_t count = 0; count < i;count++){
            mem_type_allocator.construct(tempArray+count,_dataArray[count]);
            //tempArray[count] = std::move(_dataArray[count]);
			//tempArray[count] = _dataArray[count];
            mem_type_allocator.destroy(_dataArray+count);
        }
        mem_type_allocator.construct(tempArray+i,element);
        for(std::size_t count = _nActiveE-1; count > i; count--){
            mem_type_allocator.construct(tempArray+(count),_dataArray[count-1]);
            //tempArray[count] = std::move(_dataArray[count-1]);
            //tempArray[count] = _dataArray[count-1];
            mem_type_allocator.destroy(_dataArray+count-1);
        }
		//tempArray[i] = element;
        mem_type_allocator.deallocate(_dataArray,sizeof(T));
		_dataArray = nullptr;
        //delete[] _dataArray;
		_dataArray = tempArray;
		tempArray = nullptr;
	}
	else{
		for(std::size_t count = _nActiveE-1; count > i; count--){
			_dataArray[count] = _dataArray[count-1];
		}
        mem_type_allocator.construct(_dataArray+i,element);
		//_dataArray[i] = element;



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

    mem_type_allocator.destroy(_dataArray+i);
    for(std::size_t start = i;start <_nActiveE;start++){
        _dataArray[start] = std::move(_dataArray[start+1]);
        //_dataArray[start] = _dataArray[start+1];
    }
    
    
}

//clear
template <class T>
void Vector<T>::clear(){
    for(std::size_t i = 0; i < _nActiveE ; i++) {
        mem_type_allocator.destroy(_dataArray+i);
        //delete _dataArray[i];
    }
    _nActiveE = 0;
}
//capacity
template <class T>
std::size_t Vector<T>::capacity() const {
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
        mem_type_allocator.destroy(_dataArray+i);
        mem_type_allocator.construct(_dataArray+i,T{});
        //_dataArray[i] = T{};
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
