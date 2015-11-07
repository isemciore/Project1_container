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
