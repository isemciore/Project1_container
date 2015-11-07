
#ifndef HYPERCUBE
#define HYPERCUBE
#include <iostream>
#include <vector>
template<unsigned N> class hypercube{
	std::vector<hypercube<N-1>> hypVect;
	public:
		hypercube(std::size_t width, int intData = 0)/* : hypVect(width,hypercube<N-1>(width))*/{
			for(std::size_t i = 0; i < width; i++) {hypVect.push_back(hypercube<N-1>(width,intData));}
			}
		hypercube<N-1> & operator[](unsigned int i){return hypVect[i] ;}
};
template<> class hypercube<1>{
	std::vector<int> hypVect;
	public:
		hypercube(std::size_t width, int intData=0) : hypVect(width,intData){};
		int & operator[](unsigned i){
				return hypVect[i];
		};	
};
#endif
