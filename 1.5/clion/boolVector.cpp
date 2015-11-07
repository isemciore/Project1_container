//
// Created by ezhang on 2015-10-10.
//

#include <iostream>
#include <stdexcept>
#include "boolVector.hpp"
//Constructor Vector<bool>


Vector<bool>::Vector(const std::initializer_list<bool> & initList){
    _totSize = initList.size()/bit_p_Elt +1;
    _nActiveBit = initList.size();
    _unsig_array = new unsigned int[_totSize]();
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
}

Vector<bool>::Vector(const std::size_t & reqSize)
        : _totSize(reqSize/bit_p_Elt+1)
        , _nActiveBit(reqSize) {
    _unsig_array = new unsigned int[_totSize];
}

Vector<bool>::Vector(Vector<bool> && sA) noexcept
        : _unsig_array(sA._unsig_array)
        , _totSize(sA._totSize)
        , _nActiveBit(sA._nActiveBit)
{
    sA._totSize = 0;
    sA._nActiveBit = 0;
    sA._unsig_array = nullptr;

}

Vector<bool>::Vector(const Vector<bool> & sA)
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
        //and, to set to 0. Flip all but one, then and
        _unsig_array[uSigIndex] &= ~(1u << bSubIndex);
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
    bool returnValue = ((uSigValue >> bSubIndex) % 2 != 0);
    return returnValue;
}



void Vector<bool>::printData() const{
    std::cout << "print raw unsigned values \n";
    std::cout << "this totalSize (UI L) "<< _totSize << "  :";
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




std::size_t Vector<bool>::size() const{
    return _nActiveBit;
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
    iterator temp(*this, (std::size_t) 0 );
    return temp;
}
Vector<bool>::iterator Vector<bool>::end(){
    iterator temp(*this, (std::size_t) _nActiveBit );
    return temp;
}



//bitPOINTER CONSTRUCTOR



Vector<bool>::bool_unsigProxy::~bool_unsigProxy() {}
Vector<bool>::bool_unsigProxy::bool_unsigProxy(Vector<bool> &boolData, std::size_t target)
    : targetBoolIndex(target)
    , _boolData(boolData) {}
Vector<bool>::bool_unsigProxy::bool_unsigProxy(const Vector<bool>::bool_unsigProxy &proxy)
    : targetBoolIndex(proxy.targetBoolIndex)
    , _boolData(proxy._boolData){
}
Vector<bool>::bool_unsigProxy::operator const bool() const {
    return _boolData.get_Bool(targetBoolIndex);
}

void Vector<bool>::bool_unsigProxy::operator=(bool const &sA) {
    _boolData.set_Bool(targetBoolIndex, sA);
}


bool Vector<bool>::bool_unsigProxy::operator<(const Vector<bool>::bool_unsigProxy & proxy) const {
    bool temp1 = *this;
    return temp1 < proxy;
    //return _boolData.get_Bool(targetBoolIndex) < proxy._boolData.get_Bool(proxy.targetBoolIndex);
}

bool Vector<bool>::bool_unsigProxy::operator==(Vector<bool>::bool_unsigProxy proxy) {
    return _boolData.get_Bool(targetBoolIndex) == _boolData.get_Bool(proxy.targetBoolIndex);
    //return targetBoolIndex == proxy.targetBoolIndex;
}

Vector<bool>::bool_unsigProxy &Vector<bool>::bool_unsigProxy::operator=(Vector<bool>::bool_unsigProxy &&proxy) {
    *this = proxy;
    proxy = false;
    return *this;
}
Vector<bool>::bool_unsigProxy &Vector<bool>::bool_unsigProxy::operator=(const Vector<bool>::bool_unsigProxy &proxy) {
    bool proxyBoolValue = proxy;
    *this = proxyBoolValue;
    return *this;
}


////////////////////iterator


Vector<bool>::bool_unsigProxy &Vector<bool>::iterator::operator*() {
    return bitPoint;
}

Vector<bool>::bool_unsigProxy &Vector<bool>::bool_unsigProxy::operator++() {
    targetBoolIndex++;
    return *this;
}

Vector<bool>::bool_unsigProxy &Vector<bool>::bool_unsigProxy::operator--() {
    targetBoolIndex--;
    return *this;
}

Vector<bool>::bool_unsigProxy Vector<bool>::bool_unsigProxy::operator++(int d) {
    bool_unsigProxy answer = *this;
    targetBoolIndex++;
    return answer;
}

Vector<bool>::bool_unsigProxy Vector<bool>::bool_unsigProxy::operator--(int d) {
    bool_unsigProxy answer = *this;
    targetBoolIndex--;
    return answer;
}

Vector<bool>::bool_unsigProxy& Vector<bool>::bool_unsigProxy::operator+=(int i) {
    if(((int)targetBoolIndex+i)<0){
        throw std::out_of_range("too low index");
    }
    targetBoolIndex = targetBoolIndex + i;
    return *this;
}

Vector<bool>::bool_unsigProxy& Vector<bool>::bool_unsigProxy::operator-=(int i) {
    if(((int)targetBoolIndex-i) <0)   {
        throw std::out_of_range("minus too much");
    }
    targetBoolIndex = targetBoolIndex-i;
    return *this;
}

Vector<bool>::bool_unsigProxy Vector<bool>::bool_unsigProxy::operator-(int i) {
    bool_unsigProxy answer = *this;
    answer.targetBoolIndex = answer.targetBoolIndex -i;
    return answer;
}

Vector<bool>::bool_unsigProxy Vector<bool>::bool_unsigProxy::operator+(int i) {
    bool_unsigProxy answer = *this;
    answer.targetBoolIndex = answer.targetBoolIndex +1;
    return answer;
}


/*
Vector<bool>::ptrdiff_t Vector<bool>::bool_unsigProxy::operator-(Vector<bool>::bool_unsigProxy &proxy) {
    return targetBoolIndex-proxy.targetBoolIndex;
}*/

//CONST ITERATOR
Vector<bool>::const_iterator::const_iterator(const Vector<bool> &boolData, std::size_t pointIndex)
        : bitPoint((Vector<bool> &) boolData,pointIndex){

}

Vector<bool>::bool_unsigProxy Vector<bool>::const_iterator::operator*() const {
    return bitPoint;
}


Vector<bool>::const_iterator::~const_iterator() {}


Vector<bool>::const_iterator::const_iterator(Vector<bool>::bool_unsigProxy bitPoint, std::size_t pointIndex)
    : bitPoint(bitPoint){}


Vector<bool>::ptrdiff_t Vector<bool>::const_iterator::operator-(Vector<bool>::const_iterator from) {
    return bitPoint.getTargetIndex() - from.bitPoint.getTargetIndex();
}
/*
bool Vector<bool>::const_iterator::operator==(Vector<bool>::const_iterator it) {
    return bitPoint == it.bitPoint;
}*/

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator++() {
    bitPoint++;
    return *this;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator--() {
    bitPoint--;
    return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator++(int d) {
    const_iterator answer = *this;
    bitPoint++;
    return answer;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator--(int d) {
    const_iterator answer = *this;
    bitPoint--;
    return answer;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator+=(int n) {
    bitPoint += n;
    return *this;
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator-=(int n) {
    bitPoint -= n;
    return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-(int i) {
    const_iterator answer = *this;
    answer.bitPoint -= i;
    return answer;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+(int i) {
    const_iterator answer = *this;
    answer.bitPoint += i;
    return answer;
}


//Iterator
void Vector<bool>::iterator::operator=(bool Value) {
    bitPoint = Value;
}

bool Vector<bool>::const_iterator::operator==(const Vector<bool>::const_iterator &s2) {
    return bitPoint.targetBoolIndex == s2.bitPoint.targetBoolIndex;
    //return (bitPoint == s2.bitPoint);
}
bool Vector<bool>::const_iterator::operator!=(const Vector<bool>::const_iterator &s2) {
    bool pointNotSame = (!(bitPoint.targetBoolIndex == s2.bitPoint.targetBoolIndex));
    return pointNotSame;
    //return !(bitPoint == s2.bitPoint);
}

Vector<bool>::const_iterator::const_iterator(const Vector<bool>::const_iterator &iterator)
    : bitPoint(iterator.bitPoint){
}

bool Vector<bool>::const_iterator::operator<(const Vector<bool>::const_iterator &s2) const {
    return bitPoint.targetBoolIndex < s2.bitPoint.targetBoolIndex;
}


void Vector<bool>::const_iterator::getIndex() {
    std::cout << bitPoint.getTargetIndex() << " internal pointer value \n";
}



/*
void swap(Vector<bool>::iterator &iterator, Vector<bool>::iterator &iterator1) {
    using std::swap;
    swap(*iterator,*iterator1);
    std::cout<<"swap 2\n";
}*/



Vector<bool>::iterator& Vector<bool>::iterator::operator=(const Vector<bool>::iterator& iterator) {
    bitPoint.targetBoolIndex = iterator.bitPoint.targetBoolIndex;
    //bitPoint = iterator.bitPoint;
    return *this;
}





void swap(Vector<bool>::bool_unsigProxy& buP1, Vector<bool>::bool_unsigProxy& buP2) {
    bool temp1 = buP1;
    bool temp2 = buP2;
    buP1 = temp2;
    buP2 = temp1;
}

std::size_t Vector<bool>::bool_unsigProxy::getTargetIndex() {
    return targetBoolIndex;
}
/*
size_t Vector<bool>::const_iterator::getTargetIndex() const {
    std::size_t index = bitPoint.getTargetIndex();
    return index;
}*/

Vector<bool>::iterator Vector<bool>::iterator::operator+(int i) {
    iterator answer = *this;
    answer.bitPoint += i;
    return answer;
}

Vector<bool>::iterator &Vector<bool>::iterator::operator++() {
    bitPoint++;
    return *this;
}

Vector<bool>::iterator Vector<bool>::iterator::operator++(int i) {
    iterator answer = *this;
    bitPoint++;
    return answer;
}

Vector<bool>::iterator Vector<bool>::iterator::operator-(int i) {
    iterator answer = *this;
    answer.bitPoint -= i;
    return answer;
}

Vector<bool>::ptrdiff_t Vector<bool>::iterator::operator-(Vector<bool>::iterator from) {
    return bitPoint.getTargetIndex() - from.bitPoint.getTargetIndex();
}

namespace std
{
    template <>
    void swap(Vector<bool>::iterator& p1, Vector<bool>::iterator& p2){
        Vector<bool>::iterator temp = p1;
        p1 = p2;
        p2 = temp;

    }
}
namespace std
{
    template <>
    void swap(Vector<bool>::bool_unsigProxy& v1, Vector<bool>::bool_unsigProxy& v2){
        using std::swap;
        swap(v1,v2);
    }

}

Vector<bool>::iterator &Vector<bool>::iterator::operator--() {
    bitPoint--;
    return *this;
}

Vector<bool>::iterator Vector<bool>::iterator::operator--(int i) {
    iterator answer = *this;
    bitPoint--;
    return answer;
}

