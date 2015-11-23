//
// Created by ezhang on 2015-10-10.
//

#include "boolVector.hpp"
//Constructor Vector<bool>


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










//member fun private


void Vector<bool>::set_Bool(const size_t & bitIndex, const bool & bitValue) {
    if(bitIndex >= _nActiveBit){
        throw std::out_of_range("bool set_Bool index not in range \n");
    }
    std::size_t uSigIndex = bitIndex / bit_p_Elt;
    std::size_t bSubIndex = bitIndex % bit_p_Elt;
    if(bitValue){
        //or compares both, first to 1, shift guaratees bSubIndex is true
        _unsig_array[uSigIndex] |= (1u << bSubIndex);
    }
    else{
        //and, to set to 0
        _unsig_array[uSigIndex] = ~(1u << bSubIndex);
    }
}

bool Vector<bool>::get_Bool(const size_t & bitIndex) const {
    if(bitIndex >= _nActiveBit) {
        throw std::out_of_range("bool get_Bool index not in range \n");
    }
    std::size_t uSigIndex = bitIndex / bit_p_Elt;
    std::size_t bSubIndex = bitIndex % bit_p_Elt;
    const unsigned int uSigValue = _unsig_array[uSigIndex];
    //Shift so intresting bit is at position 0 then mod 2
    return (uSigValue >> bSubIndex) % 2 != 0;
}



void Vector<bool>::printData() const{
    std::cout << "print raw unsigned values \n";
    for(std::size_t i = 0; i < _totSize;i++){
        std::cout << _unsig_array[i] << " ";
    }
    std::cout << std::endl;
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
//Operator overload
const bool Vector<bool>::operator[](const std::size_t i) const{
    const bool temp = get_Bool(i);
    return temp;
}


Vector<bool>::bool_unsigProxy Vector<bool>::operator[](const std::size_t i){
    bool_unsigProxy tempPro(*this,i);
    return tempPro;
}


Vector<bool>::const_iterator Vector<bool>::begin() const{
    return const_iterator(*this, (std::size_t) 0);
}
Vector<bool>::const_iterator Vector<bool>::end() const{
    return const_iterator(*this, (std::size_t) _nActiveBit);
}

Vector<bool>::iterator Vector<bool>::begin(){
    return iterator(*this, (std::size_t) 0);
}
Vector<bool>::iterator Vector<bool>::end(){
    return iterator(*this, (std::size_t) 0);
}