#include "SafeVector1.hpp"
#include "SafeVectPar.hpp"

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <pthread.h>
//#include "Vector.h"
SafeVectPar<int> svec(10);

void *test(void *dummy){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,9);

	for(std::size_t i = 0;i<500;i++){
		svec.safe_swap(dis(gen),dis(gen));
	}
	std::cout << "   derpderp"<< std::endl;
	pthread_exit(NULL);
}

int main(){
    std::size_t num_of_elements = 10;
	for(std::size_t i = 0; i < num_of_elements; i++){
		svec[i] = (int) i+1;
	}

    std::size_t numofThreads = 2;
	pthread_t threads[4];
	int rc;
	for(std::size_t i=0;i<numofThreads;i++){
		rc = pthread_create(&threads[i],NULL,test, (void *)i);
	
		if(rc){
			std::cout << " fail to create thread " << rc << " \n";
			exit(-1);
		}
	
	}
	void *status;
	for(std::size_t i=0;i<numofThreads;i++){
		pthread_join(threads[i],&status);
	}
		
	for(std::size_t i = 0; i<num_of_elements;i++){
		std::cout << svec[i] << ", ";
	}
    std::cout << "FInished\n";
	std::cout << "\n";
	pthread_exit(NULL);

}




