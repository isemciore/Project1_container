#include <iostream>

template<typename T>
void print(T value){
	std::cout << "awesome: "<< value << __PRETTY_FUNCTION__ << std::endl;}

int main(){
	print(3.14f);
}	
