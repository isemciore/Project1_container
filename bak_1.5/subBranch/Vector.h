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

template <>
class Vector <bool>{
	private:
		unsigned int * _unsig_array;
		std::size_t _totSize;
        std::size_t _nActiveBit;
        const static std::size_t init_size = 1; //init size
        const static int size_incr_fct = 2;   //Multi inc size
        const static std::size_t bit_p_Elt = 32;//bits per unsig
        void set_Bool(const std::size_t &, const bool &);
        bool get_Bool(const std::size_t &) const;
        
	public:
		typedef bool value_type;
		class bool_unsigProxy{
			private:
				std::size_t targetBoolIndex;
				Vector<bool>& _boolData;
			
			public:
				bool_unsigProxy(Vector<bool> & boolData,std::size_t target)
				: targetBoolIndex(target)
				, _boolData(boolData)
				{	}
				//set value via proxy 
				void operator=(bool const& sA){
					_boolData.set_Bool(targetBoolIndex,sA);
				} 
				//Get value via proxy
				operator const bool () const{
					//std::cout <<"getting value \n";
					const bool temp_value = _boolData.get_Bool(targetBoolIndex);
					return temp_value;
					
				}
			
		};
	
		class const_iterator : 
			public std::iterator<std::random_access_iterator_tag, bool>{	
			public:	//Låta operatorerna returna unsigproxy
				
				const_iterator(const Vector<bool> & boolData,std::size_t pointIndex);
				~const_iterator();/*{}*/
				bool operator*() const;
				const_iterator operator+=(int n);
				const_iterator operator-=(std::size_t n);
				bool operator==(const_iterator it);
				const_iterator& operator++();
				const_iterator& operator--();
				const_iterator operator++(int d);
				const_iterator operator--(int d);
				const_iterator operator-(std::size_t);
				const_iterator operator+(std::size_t);
				std::size_t operator-(const_iterator from);
				const_iterator& operator=(const_iterator const& sA); //assigncopy
				bool operator<(const const_iterator &s2){
				if(_boolData.get_Bool(currentIndex) < s2._boolData.get_Bool(s2.currentIndex))
					return true;
				else
					return false;
				}
				
				bool operator !=(const const_iterator &s2){
				if(currentIndex == s2.currentIndex){
					return false;
					}	
				return true;
				}
				
			protected:
				std::size_t currentIndex;//public så iterator också har tillgång
				const Vector<bool>& _boolData;
				
			private:
			
		};
		class iterator: public const_iterator{ ///vid ansätta värde casta om const till const_cast bort referensens
			public:
				using const_iterator::const_iterator;
				//iterator(const Vector<bool>& boolData,std::size_t pI)
				//: const_iterator(boolData,pI){}
				void operator=(bool Value){
					const_cast<Vector<bool>&>(_boolData).set_Bool(currentIndex,Value);
				}
				
				iterator& operator=(iterator const& it){
					if(this==&it) return *this;
					const_cast<Vector<bool>&>(_boolData) = const_cast<Vector<bool>&>(it._boolData);
					currentIndex = it.currentIndex;
					return *this;
				}
				
				bool_unsigProxy operator*(){
					return bool_unsigProxy(const_cast<Vector<bool>&>(_boolData), currentIndex);
				}
				
				friend void swap(iterator& p1, iterator& p2);
				
				
				
			private:
			
		};
		const_iterator begin() const;
		const_iterator end() const;
		iterator begin();
		iterator end();
		void constFun() const;
		void normalFun();
		void printData() const;
		explicit Vector(); //def init
        ~Vector(); //destruct
        Vector<bool>& operator=(Vector<bool> && sA); //move assign
        Vector<bool>& operator=(Vector<bool> const& sA);
        Vector(Vector &&) noexcept; //move
        Vector(const Vector &); 
        /*
        //copy
        Vector<T>& operator=(Vector<T> const& sA); //Assigncopy
        */
        explicit Vector(const std::size_t &);
        Vector(const std::size_t &,const bool &); 
        Vector(const std::initializer_list<bool> &);
        /* 
        std::size_t size() const ;*/
        void push_back(const bool&);
		//std::back_insert_iterator<Vector<bool>> back_inserter(Vector<bool>& c);
        const bool operator[](const std::size_t i) const;
        bool_unsigProxy operator[](const std::size_t i);
         
        
};

namespace std
{
    template<> 
    void swap(Vector<bool>::iterator& p1, Vector<bool>::iterator& p2){
	bool tempBool = *p1;
	bool temp2Bool = *p2;
	*p1 = temp2Bool;
	*p2 = tempBool;
	
	}
}






//////BOOL CASE
///Iterator const
Vector<bool>::const_iterator::const_iterator(const Vector<bool> & boolData,std::size_t pointIndex)
	: currentIndex(pointIndex)
	, _boolData(boolData){}
	
Vector<bool>::const_iterator::~const_iterator(){}

bool Vector<bool>::const_iterator::operator*() const{
	bool temp = _boolData.get_Bool(currentIndex);
	return temp;
}


Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-=(std::size_t n){
	if(currentIndex -n >=0 && currentIndex-n <= _boolData._nActiveBit){
		currentIndex = currentIndex-n;
		return *this;
	}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+=(int n){
	int tempCurId = (int) currentIndex;
	if(tempCurId + n >= 0 && tempCurId + n <= (int) _boolData._nActiveBit){
		currentIndex = ((std::size_t) (tempCurId+n));
		return *this;
	}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}

bool Vector<bool>::const_iterator::operator==(const_iterator it){
	if (it.currentIndex == currentIndex){
		return true;
	}
	return false;
	
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator++(){
	if(currentIndex+1 <= _boolData._nActiveBit){
		currentIndex++; 
		return *this;
		}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}
Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator--(){
	if(currentIndex == 0){
		throw std::out_of_range("bool index not in range \n");
		return *this;}
	currentIndex--;
	return *this;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator++(int d){
	if(currentIndex==_boolData._nActiveBit){
		throw std::out_of_range("bool index not in range \n");
		return *this;
	}
	const_iterator ans = *this; 
	currentIndex++; 
	return ans;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator--(int d){
	if(currentIndex==0){
		throw std::out_of_range("bool index not in range \n");
		return *this;
	}
	const_iterator ans = *this; 
	currentIndex--; 
	return ans;
}
				
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-(std::size_t n){
	const_iterator ans = *this;
	ans-=(n);
	return ans;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+(std::size_t n){
	const_iterator ans = *this;
	ans+=(n);
	return ans;
}

std::size_t Vector<bool>::const_iterator::operator-(const_iterator from){
	return (currentIndex - from.currentIndex);
}


/*
Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator=(const_iterator const& sA){ //assigncopy
	if(this==&sA) return *this;
    _boolData = sA._boolData;
    currentIndex = sA.currentIndex;
    return *this;			
}*/








/*
///Iterator non const
Vector<bool>::iterator::iterator(Vector<bool> & boolData,std::size_t pointIndex)
	: currentIndex(pointIndex)
	, _boolData(boolData){}
*/
///Init Iterator
Vector<bool>::const_iterator Vector<bool>::begin() const{
	const_iterator tempIterator(*this,(std::size_t) 0);
	return tempIterator;
}
Vector<bool>::const_iterator Vector<bool>::end() const{
	const_iterator tempIterator(*this,_nActiveBit);
	return tempIterator;
}


Vector<bool>::iterator Vector<bool>::begin(){
	const Vector<bool> & tempConst = *this;
	iterator tempIterator(tempConst,(std::size_t) 0);
	//iterator tempIterator(*this,(std::size_t) 0);
	return tempIterator;	
}

Vector<bool>::iterator Vector<bool>::end(){
	iterator tempIterator(*this,_nActiveBit);
	return tempIterator;
}

//Bool Constructor

const bool Vector<bool>::operator[](const std::size_t i) const{
	const bool temp = get_Bool(i);
	return temp;
}
Vector<bool>::bool_unsigProxy Vector<bool>::operator[](const std::size_t i){
	bool_unsigProxy tempPro(*this,i);
	return tempPro;
}



Vector<bool>::Vector()
    : _totSize(init_size)
    , _nActiveBit(0)
{
	_unsig_array = new unsigned int [init_size];
	std::cout << "default init\n";
}
Vector<bool>::Vector(const std::size_t & reqSize)
	: _totSize(reqSize/bit_p_Elt+1)
	, _nActiveBit(reqSize) {
	_unsig_array = new unsigned int[_totSize];
	std::cout << "size initilizer \n";
}

Vector<bool>::Vector(Vector && sA) noexcept
	: _unsig_array(sA._unsig_array)
	, _totSize(sA._totSize)
	, _nActiveBit(sA._nActiveBit)
{
	sA._totSize = 0;
	sA._nActiveBit = 0;
	sA._unsig_array = nullptr;	
	
}

Vector<bool>::Vector(const Vector & sA)
	: _totSize(sA._totSize)
	, _nActiveBit(sA._nActiveBit)
	{
	_unsig_array = new unsigned int[_totSize];
	for(std::size_t i = 0; i < _nActiveBit/bit_p_Elt +1 ; i++){
		_unsig_array[i] = sA._unsig_array[i];
	}
}




Vector<bool>::~Vector(){
	delete[] _unsig_array;
}

Vector<bool>::Vector(const std::size_t & reqSize, const bool & value){
	_totSize = reqSize/bit_p_Elt +1;
	_nActiveBit = reqSize;
	_unsig_array = new unsigned int[_totSize];
	std::cout << "Size initilizer with init value \n";
	//Default set all to 0
	for(std::size_t uIndex = 0; uIndex < _totSize ; uIndex ++){
			_unsig_array[uIndex] = 0;
	}
	if(value){ //Set all to "true" performimg bit op.	
		for(std::size_t boolIndex = 0; boolIndex < reqSize; boolIndex++){
			set_Bool(boolIndex,true);
		}
	}
}


//Vector<T>& Vector<bool>::operator=(Vector<T> && sA); //move assign
//Move assignment
Vector<bool>& Vector<bool>::operator=(Vector<bool> && sA){
    if(this==&sA){ return *this;}
    
	delete[] _unsig_array;
		_unsig_array = sA._unsig_array;
		_totSize = sA._totSize;
		_nActiveBit = sA._nActiveBit;
		sA._unsig_array = nullptr;
		sA._totSize = 0;
		sA._nActiveBit = 0;
    return *this;
}
Vector<bool>& Vector<bool>::operator=(Vector<bool> const& sA){//AssignCopy
	if(this==&sA) return *this;
	
	delete[] _unsig_array;
	_totSize = sA._totSize;
	_nActiveBit = sA._nActiveBit;
	_unsig_array = new unsigned int [_totSize];
	for(std::size_t i = 0; i < _nActiveBit/bit_p_Elt+1;i++){
		_unsig_array[i] = sA._unsig_array[i];
	}
	return *this;

}





//list init
Vector<bool>::Vector(const std::initializer_list<bool> & initList){
	_totSize = initList.size()/bit_p_Elt +1;
	_nActiveBit = initList.size();
	_unsig_array = new unsigned int[_totSize];
	
	std::size_t counter = 0;
    for(auto &elt : initList){
		set_Bool(counter,elt);
		counter++;
	}
}




void Vector<bool>::constFun() const{
	std::cout << "const function" << "\n";
}
void Vector<bool>::normalFun(){
	std::cout << "normal function" << "\n";
}

void Vector<bool>::set_Bool(const std::size_t & boolIndex, const bool & boolValue){
	if(boolIndex >= _nActiveBit){
        throw std::out_of_range("bool index not in range \n");}
	std::size_t uSigIndex = boolIndex / bit_p_Elt;
	std::size_t bSubIndex = boolIndex % bit_p_Elt;
	if(boolValue){
		//or - compares both, set first index to 1, then shift bsub steps. 
									//Guaratees index bSubIndex will be 1
									//if 1 is in either, that index is set to 1
		_unsig_array[uSigIndex] |= (1u << bSubIndex);
	}
	else{
		//And set to 1 only if both sides is true
								// not converts 00001 to 11110 and then and operation
		_unsig_array[uSigIndex] &= ~(1u << bSubIndex);
	}
}

bool Vector<bool>::get_Bool(const std::size_t & boolIndex) const{
	if(boolIndex >= _nActiveBit){
		throw std::out_of_range("bool index not in range \n");
	}
	std::size_t uSigIndex = boolIndex / bit_p_Elt;
	std::size_t bSubIndex = boolIndex % bit_p_Elt;
	
	const unsigned int & uSigValue = _unsig_array[uSigIndex];
	//takes out the unsig value, then shift it so the interesting 
	//bit is located at index 0, then mod 2 to determine if it is 1 or 0
	//and makes appropriate return value.
	if( (uSigValue >> bSubIndex)%2){
		return true;
	}
	return false; 
	
}

void Vector<bool>::printData() const{
	std::cout << "print raw unsigned values \n";
	for(std::size_t i = 0; i < _totSize;i++){
		std::cout << _unsig_array[i] << " ";
	}
	std::cout << std::endl;
	/*std::cout << "printing corresponding bool values\n";
	for(std::size_t i = 0; i < _nActiveBit;i++){
		std::cout << get_bool(i) <<" ";
	}
	std::cout << "\n";*/
}

void Vector<bool>::push_back(const bool & element){
    //std::cout << "pushbackar \n";
    _nActiveBit++;
    if (_nActiveBit/bit_p_Elt +1 > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
        
        unsigned int * tempArray = new unsigned int[_totSize];
        for(std::size_t count = 0; count < _nActiveBit/bit_p_Elt;count++){
			tempArray[count] = _unsig_array[count];}
		if(element){tempArray[_nActiveBit/bit_p_Elt] = 1;}
		else{tempArray[_nActiveBit/bit_p_Elt] = 0;}
        delete[] _unsig_array;
        _unsig_array = tempArray;
        tempArray = nullptr;
    }
    else{
		set_Bool(_nActiveBit-1,element);
	}    
}
/*
std::back_insert_iterator<Vector<bool>> Vector<bool>::back_inserter(Vector<bool>& c)
{
    return std::back_insert_iterator<Vector<bool>>(c);
}
*/



////////DEFAULT TEMPALTE T

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
