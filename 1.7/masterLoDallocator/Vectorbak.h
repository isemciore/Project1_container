#include <iostream>
#include <cstring>
#include <stdexcept> 
#include <algorithm> 
#include <initializer_list>
#include <type_traits>
#include <iterator>
#ifndef SUPERARRAY
#define SUPERARRAY
//DROPBOX BACKUP SÖNDAG 11 OKT FÖR OK VERSION

template <class T> 
class Vector {
    private:
        std::size_t startPointerIndex = 0;
        std::size_t _totSize = 32;
        std::size_t _nActiveE=0;
        const static std::size_t init_size = 32; //init size
        const static std::size_t init_add_size = 5;
        const static int size_incr_fct = 2;   //Multi inc size
        T **_dataArray;
        void checkType();
    
    public:
        typedef bool value_type;
        typedef long ptrdiff_t;


        class const_iterator : public std::iterator<std::random_access_iterator_tag, bool> {
        public:
            const_iterator(T** & d_array, std::size_t currentIndex);
            const_iterator(T** const & d_array, std::size_t currentIndex);
            ~const_iterator();
            const_iterator(const const_iterator&);
            const_iterator& operator=(const const_iterator & );
            bool operator==(const const_iterator &sA);

            bool operator!=(const const_iterator &sA);
            const_iterator& operator+=(int n);
            const_iterator& operator-=(int n);
            const_iterator& operator++();
            const_iterator& operator--();
            //const_iterator& operator= (const_iterator && source);
            const_iterator operator--(int n);
            const_iterator operator++(int n);
            const_iterator operator-(int n);
            const_iterator operator+(int n);
            std::size_t    operator-(const const_iterator &);
            //operator const T () const; //Get value
            const T& operator*();//get value

        protected:
            T** & _d_array;
            std::size_t _currentIndex;
        };

    class iterator : public const_iterator {
            private:
            public:
                T& operator*();//return reference
            using const_iterator::const_iterator;
        };

        explicit Vector(); //def init
        ~Vector(); //destruct
        Vector(const Vector &); //copy
        Vector(Vector &&) noexcept; //move
        Vector<T>& operator=(Vector<T> && sA); //move assign
        Vector<T>& operator=(Vector<T> const& sA); //Assigncopy
        explicit Vector(const std::size_t &);
        Vector(const std::size_t &,const T &);
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
        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();
        iterator find(T const & target);
        const_iterator find(T const & target) const;
        void reset();
};

/*
std::back_insert_iterator<Vector<bool>> Vector<bool>::back_inserter(Vector<bool>& c)
{
    return std::back_insert_iterator<Vector<bool>>(c);
}
*/



////////DEFAULT TEMPALTE T

//Initlist
template <class T>
Vector<T>::Vector(const std::initializer_list<T> & bigData)
    {
	//std::cout << "initlist trigger \n";
    _totSize = bigData.size();
    _nActiveE = bigData.size();

    _dataArray = new T*[_totSize];

    std::size_t counter = 0;
    for(auto &elt : bigData){
		_dataArray[counter] = new T(elt);
		counter++;
	}
    startPointerIndex = 0;
	
}





template <class T>
Vector<T>::Vector(const std::size_t & reqSize){
    checkType();
    _totSize = reqSize;
    _nActiveE = reqSize;
    _dataArray = new T*[_totSize];
    startPointerIndex = 0;
    //std::cout << "size init\n";
    for(std::size_t i = 0; i < _totSize; i++){
        _dataArray[i] = new T{};
    }
}
template <class T>
Vector<T>::Vector(const std::size_t & reqSize,const T & data){
    checkType();
    _totSize = reqSize;
    _nActiveE = reqSize;
    startPointerIndex = 0;
    _dataArray = new T*[_totSize];
    for(std::size_t i = 0; i < _totSize; i++){
        _dataArray[i] = new T(data);
    }
}

//Default
template <class T> 
Vector<T>::Vector()
    : _totSize(init_size)
    , _nActiveE(0)
    //, _dataArray(new T [init_size])
{

    _dataArray = new T*[_totSize];
    checkType();
    //_nActiveE=0;
    //_totSize = init_size;
    //_nActiveE = 0;
    //std::cout<<"default constructor"<<"\n";
    //_dataArray = new T [init_size];
    startPointerIndex = 0;
}
//Destroy
template <class T> Vector<T>::~Vector(){
    if(_dataArray) {
        //std::cout << "destroy trigg\n";
        for (std::size_t i = startPointerIndex; i < _nActiveE + startPointerIndex; i++) {
            delete _dataArray[i];
        }
        delete[] _dataArray;
    }
}
//Copy constructor
template <class T> Vector<T>::Vector(const Vector &ar){
    checkType();
    _totSize = ar._nActiveE;
    _nActiveE = ar._nActiveE;
    startPointerIndex = 0;
    _dataArray = new T*[_totSize];
    for(std::size_t i = 0; i < _nActiveE; i++){
		_dataArray[i] = new T( (*ar._dataArray[i])) ;
	}
	
    //memcpy(_dataArray,ar._dataArray,sizeof(T)*_totSize);
}
//Move
template <class T>
Vector<T>::Vector(Vector &&sA) noexcept
    : _totSize(sA._nActiveE)
{
    checkType();
    _nActiveE = sA._nActiveE;

    _dataArray = new T*[_totSize];

    startPointerIndex =0;
    for(std::size_t i= 0; i < _nActiveE ; i++){
        _dataArray[i] = sA._dataArray[i];
        sA._dataArray[i] = nullptr;}
    sA.startPointerIndex = 0;
    sA._nActiveE = 0;
}
//Move assignment
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> && sA){
    if(this==&sA) return *this;
    for (std::size_t i = startPointerIndex; i < _nActiveE + startPointerIndex; i++) {
        delete _dataArray[i];
    }
    delete[] _dataArray;
    _dataArray = sA._dataArray;
    startPointerIndex = sA.startPointerIndex;
    _totSize = sA._totSize;
    _nActiveE = sA._nActiveE;
    sA._dataArray = nullptr;
    sA._totSize = 0;
    sA._nActiveE =0;
    return *this;
}


//Assignment copy via = 
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& sA){
    if(this==&sA) return *this;
    for (std::size_t i = startPointerIndex; i < _nActiveE + startPointerIndex; i++) {
        delete _dataArray[i];
    }
    delete[] _dataArray;
    _totSize = sA._nActiveE;
    _nActiveE = sA._nActiveE;
    startPointerIndex = 0;
    _dataArray = new T*[_totSize];
    for(std::size_t i = 0; i < _nActiveE ; i++){
        _dataArray[i] = new T(*sA._dataArray[i]);
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
    const T& value = *_dataArray[i+startPointerIndex];
    return value;
}
        
template <class T>      
T & Vector<T>::operator[](const size_t i) { 
    //std::cout <<"DOING THE [] OPERATOR \n";
    if(i >= _nActiveE){
        throw std::out_of_range("index not in range");}
    return *_dataArray[i+startPointerIndex];
}



//pushback
template <class T>
void Vector<T>::push_back(const T  & element){
    //std::cout << "pushbackar \n";
    T copyT = element;
    _nActiveE++;
    if (_nActiveE+startPointerIndex > _totSize){

        _totSize = _totSize*size_incr_fct + init_add_size;
        T** tempArray;
        tempArray = new T*[_totSize];

        for(std::size_t count = 0; count < _nActiveE-1;count ++){
            tempArray[count] = _dataArray[count + startPointerIndex];
            _dataArray[count+startPointerIndex] = nullptr;
            delete _dataArray[count+startPointerIndex];
        }
        delete[] _dataArray;
        startPointerIndex = 0;
        _dataArray = tempArray;
        tempArray = nullptr;

    }
    _dataArray[_nActiveE-1+startPointerIndex] = new T(element);


}
//INSERT
template <class T>
void Vector<T>::insert(const std::size_t & i,const T & element){
    if(i > _nActiveE){
        throw std::out_of_range("index not in range");}
    //std::cout << "Insert \n";
    _nActiveE++;
    if(_nActiveE+startPointerIndex > _totSize) {
        _totSize = _totSize * size_incr_fct + init_add_size;
    }

    T** tempArray;//redeclaration
    tempArray = new T*[_totSize];
    for(std::size_t count = 0; count < i;count++){
        tempArray[count] = _dataArray[count+startPointerIndex];
        _dataArray[count+startPointerIndex] = nullptr;
        delete _dataArray[count+startPointerIndex];
    }
    for(std::size_t count = _nActiveE-1; count > i; count--){
        tempArray[count] = _dataArray[count-1+startPointerIndex];
        _dataArray[count-1+startPointerIndex] = nullptr;
        delete _dataArray[count-1+startPointerIndex];
    }
    delete[] _dataArray;
    _dataArray = tempArray;
    _dataArray[i] = new T(element);
    startPointerIndex = 0;

}



//erase
template <class T>
void Vector<T>::erase(const std::size_t & i){
    if(i > _nActiveE){
        std::cout << i << " is the target " << _nActiveE << "true number of elements"<< "\n";
        throw std::out_of_range("index not in range");}
    //_dataArray[i-1].~T();
    std::size_t eraseIndex = i+startPointerIndex;

    (*_dataArray[eraseIndex]).~T();
    _dataArray[eraseIndex] = nullptr;
    delete _dataArray[eraseIndex];
    for(std::size_t counter = eraseIndex; counter > startPointerIndex; counter--) {
        //_dataArray[counter].~T();
        _dataArray[counter] = _dataArray[counter-1];
    }
    //_dataArray[0] = nullptr;
    //delete _dataArray[0];
    _nActiveE--;
    startPointerIndex++;

}

//clear
template <class T>
void Vector<T>::clear(){
    for(std::size_t i = startPointerIndex; i < _nActiveE + startPointerIndex; i++) {
        delete _dataArray[i];
    }
    startPointerIndex=0;
    _nActiveE =0;
}









//capacity
template <class T>
std::size_t Vector<T>::capacity() const{
    return _totSize;
}



template <class T>
typename Vector<T>::iterator Vector<T>::begin(){
    iterator temp = iterator(_dataArray, (std::size_t ) 0);
    return temp;
}
template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const{
    const_iterator temp = const_iterator(_dataArray,(std::size_t ) 0);
    return temp;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end(){
    return iterator(_dataArray,_nActiveE);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const{
    return const_iterator(_dataArray,_nActiveE);
}


template <class T>
typename Vector<T>::iterator Vector<T>::find(T const & target){
    for(std::size_t i = 0; i < _nActiveE;i++){
        if(*_dataArray[i] == target){
            return iterator(_dataArray,i);
        }
    }
    return iterator(_dataArray,_nActiveE);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::find(T const & target) const{
    for(std::size_t i = 0; i < _nActiveE;i++){
        if(*_dataArray[i] == target){
            return const_iterator(_dataArray,i);
        }
    }
    return const_iterator(_dataArray,_nActiveE);
}

template <class T>
void Vector<T>::checkType(){
    static_assert ( std::is_move_assignable<T>::value , "not move assignable" );
    static_assert ( std::is_move_constructible<T>::value , "not move constructible" );
}

template <class T>
void Vector<T>::reset(){
    for(std::size_t i = 0; i < _nActiveE;i++){
        delete _dataArray[i];
        _dataArray[i] = new T{};
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


template <class T>
Vector<T>::const_iterator::const_iterator(T** & d_array, std::size_t currentIndex)
        : _d_array(d_array)
        , _currentIndex(currentIndex){}

template <class T>
Vector<T>::const_iterator::const_iterator(T** const & d_array, std::size_t currentIndex)
        : _d_array((T **&) d_array)
        , _currentIndex(currentIndex){}

template <class T>
Vector<T>::const_iterator::const_iterator(const const_iterator& sA)
    : _d_array(sA._d_array)
    , _currentIndex(sA._currentIndex){
}
template <class T>
typename Vector<T>::const_iterator & Vector<T>::const_iterator::operator=(const const_iterator& iterator){
    _d_array = iterator._d_array;
    _currentIndex = iterator._currentIndex;
    return *this;
}

template <class T>
Vector<T>::const_iterator::~const_iterator() {
}

template <class T>
bool Vector<T>::const_iterator::operator==(const Vector<T>::const_iterator &sA) {
    return _currentIndex == sA._currentIndex;
}

template <class T>
bool Vector<T>::const_iterator::operator!=(const Vector::const_iterator &sA) {
    return !(_currentIndex==sA._currentIndex);
}
template <class T>
typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator+=(int n) {
    if((int) _currentIndex +n < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    _currentIndex += n;
    return *this;
}
template <class T>
typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator-=(int n) {
    if((int) _currentIndex -n < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    _currentIndex -=n;
    return *this;
}
template <class T>
typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator++() {
    _currentIndex++;
    return *this;
}
template <class T>
typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator--() {
    if((int) _currentIndex -1 < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    _currentIndex--;
    return *this;
}
/*
Vector::const_iterator &Vector::const_iterator::operator=(Vector::const_iterator &&source) {

    return *this;
}*/

template <class T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator--(int n) {
    if((int) _currentIndex -1 < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    Vector::const_iterator answer = *this;
    _currentIndex--;
    return answer;
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator++(int n) {
    Vector::const_iterator answer = *this;
    _currentIndex++;
    return answer;
}
/*
template <class T>
Vector<T>::const_iterator::operator const T() const{
    const T& answer = *_d_array[_currentIndex];
    return answer;
}*/

template <class T>
const T& Vector<T>::const_iterator::operator*() {
    const T& answer = *_d_array[_currentIndex];
    return answer;
}


template <class T>
T& Vector<T>::iterator::operator*() {
    T& answer = *const_iterator::_d_array[const_iterator::_currentIndex];
    return answer;
}



template <class T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator-(int n) {
    if((int) _currentIndex -n < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    const_iterator answer = *this;
    answer._currentIndex = answer._currentIndex-n;
    return answer;
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator+(int n) {
    if((int) _currentIndex +n < 0){
        throw std::out_of_range{"never reach here.. 1"};
    }
    const_iterator answer = *this;
    answer._currentIndex = answer._currentIndex +n;
    return answer;
}


template <class T>
typename std::size_t Vector<T>::const_iterator::operator-(const Vector<T>::const_iterator& iterator) {
    return _currentIndex-iterator._currentIndex;
}


#endif

