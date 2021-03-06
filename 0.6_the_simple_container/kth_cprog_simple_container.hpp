#ifndef CUSTOMVECTOR
#define CUSTOMVECTOR

#include <initializer_list>
#include <cstring>

using size_type = unsigned int;
using array_type = unsigned int;
class UIntVector

{
	private:
		size_type usedElements;
		size_type currentLength;
		array_type *uArray;
		
	public:
		//constructor
		UIntVector ();
		explicit UIntVector(std::size_t nElts);
		UIntVector(std::initializer_list<unsigned int> bigData);
		UIntVector (UIntVector const& src);
		~UIntVector();
		UIntVector& operator= (UIntVector const& src);

		UIntVector(UIntVector&&) noexcept;
		UIntVector& operator= (UIntVector &&);		

		//Method		
		//const []		
		const array_type operator[](const size_t i) const;
		void operator++(const int i);
		//assignment		
		array_type& operator[](const size_t i);
		
		size_type getusedElements() const;
		size_type getcurrentLength() const;
		array_type * getDataPoint() const;
		std::size_t size() const;
		void reset();
		
		//void cleanPrivPoint();
	

};

#endif
//	#include "UIntVector.h"
#include <iostream>
#include <cstring>
#include <stdexcept>  
#include <initializer_list>

//DEFAULT array_type = unsigned int
//	  size_type = unsigned int

UIntVector::UIntVector () {
	uArray = new array_type[0];
	//std::cout << "default-constructor" << std::endl;
}

UIntVector::UIntVector(std::size_t nElts) 
	: uArray(new array_type[nElts]()) 
	//, currentLength{nElts}
	/*, usedElements(nElts)*/ {
	//std::cout <<"SINGLE ELT CONSTRUCTOR";
	//uArray = new unsigned int[nElts]();
	currentLength = nElts;
	usedElements = nElts; 
}
		
UIntVector::UIntVector(std::initializer_list<array_type> bigData){
	currentLength = bigData.size();
	usedElements = bigData.size();
	const array_type * startP = bigData.begin();
	uArray = new array_type[currentLength];
	std::memcpy(uArray,startP,sizeof(array_type)*usedElements);
	//std::cout <<"std initlizer-list \n";
}
		

UIntVector::UIntVector (UIntVector const& src) {
	currentLength = src.currentLength;
	usedElements = src.usedElements;
	uArray  = new array_type[currentLength];
	std::memcpy(uArray,src.uArray,sizeof(array_type)*usedElements);
	//std::cout << "copy-constructor" << std::endl;
}

UIntVector::~UIntVector () {
	delete[] uArray;
	//std::cout << "destructor" << std::endl;
}

//Move constructor
UIntVector::UIntVector(UIntVector &&s) noexcept 
	: uArray(s.getDataPoint())
	//, currentLength(s.currentLength)
	//, usedElements(s.usedElements)
	//, usedElements(s.getusedElements())
	//, currentLength(s.getcurrentLength())
{
	currentLength = s.currentLength;
	usedElements = s.usedElements;
	//std::cout << "MOVING STUFF\n";
	s.uArray = nullptr;
	s.usedElements = 0;
	s.currentLength = 0;
	//s.cleanPrivPoint();
//	s.uArray = s.usedElements = s.currentLength = nullptr;
}

//Move already initiated 
UIntVector& UIntVector::operator= (UIntVector &&s){
	//std::cout << "MOVE ASSIGNMENT";
	if(this==&s) return *this;
	delete[] uArray;
	uArray = s.uArray;
	currentLength = s.currentLength;
	usedElements = s.usedElements;
	s.uArray = nullptr;
	s.usedElements = 0;
	s.currentLength = 0;
	
	return *this;
}

//Copy via assignment
UIntVector& UIntVector::operator= (UIntVector const& src) {
	if(this==&src) return *this;
	delete[] uArray;
	currentLength = src.currentLength;
	usedElements = src.usedElements;
	uArray = new array_type [currentLength];
	memcpy(uArray,src.uArray,sizeof(array_type)*usedElements);
	//std::cout << "the assignment operator" << std::endl;
	return *this;
}

const array_type UIntVector::operator[](const size_t i) const{
	//std::cout <<"CONST GET VALUE";
	if(i<0 || ((size_type) i >= usedElements)){
		throw std::out_of_range("index not in range");}
	const array_type value = uArray[i];
	return value;
}		
		
array_type& UIntVector::operator[](const size_t i) { 
	//std::cout <<"DOING THE [] OPERATOR \n";
	//std::cout <<"int i : "<< i <<"    " << usedElements<<"\n";
	
	if(i<0 || ((size_type) i >= usedElements)){
		throw std::out_of_range("index not in range");}
	return uArray[i];
}
		
void UIntVector::operator++(const int i){
	if(i<0 || ((size_type) i >= usedElements)){
		throw std::out_of_range("index not in range");}
	uArray[i] = uArray[i]+1;
}		
		
				
void UIntVector::reset(){
	for(unsigned int i=0;i<currentLength;i++){
		uArray[i] = 0;
	}
}


size_type UIntVector::getusedElements() const {
	return usedElements;
}
		
size_type UIntVector::getcurrentLength() const {
	return currentLength;
}
		
size_type * UIntVector::getDataPoint() const {
	return uArray;
}
		
std::size_t UIntVector::size() const {
	return (std::size_t) usedElements;
}
		

	
	
