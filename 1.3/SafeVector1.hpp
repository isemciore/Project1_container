#ifndef SAFEVECTOR_1
#define SAFEVECTOR_1
#include "Vector.hpp"
#include <atomic>
#include <thread>



template <class T> 
class SafeVector1 : public Vector<T>{
	public:
		using Vector<T>::Vector;
		void safe_swap(std::size_t from, std::size_t to);
	private:
		std::atomic_flag isBusy = ATOMIC_FLAG_INIT;

};


template<class T>
void SafeVector1<T>::safe_swap(std::size_t from, std::size_t to){
    while(isBusy.test_and_set(std::memory_order_acquire)){
		std::this_thread::yield();
	}
    Vector<T>::unsafeSwap(from,to);
    isBusy.clear(std::memory_order_release);
    
}



#endif
