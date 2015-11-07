#ifndef CUSTOMVECTOR
#define CUSTOMVECTOR

#include <cstring>
class UIntVector
{
	public:

		unsigned int getusedElements() const;
		unsigned int getcurrentLength() const;
		unsigned int * getDataPoint() const;
		std::size_t size() const;
		unsigned int& operator[](const int i);
};

#endif
