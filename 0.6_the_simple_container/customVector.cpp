#include <iostream>
#include <cstring>
#include <stdexcept>   

#include <initializer_list>

class UIntVector{
	public:
		UIntVector () {
			uArray = new unsigned int[0];
			std::cout << "default-constructor" << std::endl;
		}
		
		
		explicit UIntVector(std::size_t nElts){
			uArray = new unsigned int[nElts]();
			currentLength = nElts;
			usedElements = 0; 
		}
		
		UIntVector(std::initializer_list<unsigned int> bigData){
			currentLength = bigData.size();
			usedElements = bigData.size();
			const unsigned int * startP = bigData.begin();
			uArray = new unsigned int[currentLength];
			std::memcpy(uArray,startP,sizeof(unsigned int)*usedElements);
			std::cout <<"std initlizer-list \n";
		}
		

		UIntVector (UIntVector const& src) {
			currentLength = src.currentLength;
			usedElements = src.usedElements;
			uArray  = new unsigned int[currentLength];
			std::memcpy(uArray,src.uArray,sizeof(unsigned int)*usedElements);
			std::cout << "copy-constructor" << std::endl;
		}

		~UIntVector () {
			delete[] uArray;
			std::cout << "destructor" << std::endl;
		}


		UIntVector& operator= (UIntVector const& src) {
			if(this==&src) return *this;
			delete[] uArray;
			currentLength = src.currentLength;
			usedElements = src.usedElements;
			uArray = new unsigned int [currentLength];
			memcpy(uArray,src.uArray,sizeof(unsigned int)*usedElements);
			std::cout << "the assignment operator" << std::endl;
			return *this;
		}
		
		//unsigned int& operator[](const unsigned int idRel){
		//	return uArray[idRel];
		//}
		
		
		unsigned int& operator[](const int i) { 
			if(i<0 || ((unsigned int) i >= usedElements)){
				throw std::out_of_range("index not in range");}
			return uArray[i];
		}
		
				
		void reset(){
			for(unsigned int i=0;i<currentLength;i++){
				uArray[i] = 0;
			}
		}
		unsigned int getusedElements() const {
			return usedElements;
		}
		
		unsigned int getcurrentLength() const {
			return currentLength;
		}
		
		unsigned int * getDataPoint() const {
			return uArray;
		}
		
		std::size_t size() const {
			return (std::size_t) usedElements;
		}
		
	private:
		unsigned int usedElements;
		unsigned int currentLength;
		unsigned int *uArray;
};


/*
int main(){
	std::cout<<"start";
	for(int i=0; i < 10;++i){
		std::cout<<i<<"\n";
	}
	
	int testArray [] = {1,2,3,4,5};
	std::cout << testArray[2];
	
	std::cout <<"test\n";
	std::size_t siffra = 5;

	


	UIntVector testVector(siffra);
	
	unsigned int * extractor = testVector.getDataPoint();
	
	
	UIntVector langTest = {1,2,3,4,5,6,7,8};
	langTest[5] = 20;
	unsigned int siff = langTest[5];
	
	std::cout<<"DERP"<< siff <<std::endl;
	//langTest[2] = 1;
	
	extractor = langTest.getDataPoint();
	std::cout << langTest[4];

	std::cout<<*extractor<<"\n";
	UIntVector derp(testVector);
	extractor = testVector.getDataPoint();
	std::cout<<*extractor<<"\n";
	
	UIntVector serp;
	serp = langTest;
	std::cout << langTest[6];
	
	//UIntVector *testDestrukt = new UIntVector[2];
	//delete[] testDestrukt;
	
	std::cout <<"test\n";
}
	*/
	
	
