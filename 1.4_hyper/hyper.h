
#ifndef HYPERCUBE
#define HYPERCUBE
#include <iostream>
#include <vector>
template<unsigned N> class hypercube : public std::vector<hypercube<N-1>>{
	public:
        hypercube(std::size_t width) : std::vector<hypercube<N-1>>(width,hypercube<N-1>(width)){};
            /*
			for(std::size_t i = 0; i < width; i++) {(*this).push_back(hypercube<N-1>(width,intData));}
			}*/
		using std::vector<hypercube<N-1>>::operator[];
		//hypercube<N-1>& operator[](unsigned int i){return (std::vector<hypercube<N-1>>[i]);}
};
template<> class hypercube<1> : public std::vector<int>{
	public:
		hypercube(std::size_t width, int intData=0) : std::vector<int>(width,intData){};
		using std::vector<int>::operator[];
};
#endif
