#include <iostream>

class A {
public:
   A () {
     std::cout << "default-constructor" << std::endl;
   }

   A (A const& src) {
     std::cout << "copy-constructor" << std::endl;
   }

  ~A () {
    std::cout << "destructor" << std::endl;
  }

   A(char const* s) {
      std::cout << "some other constructor" << std::endl;
   }

   A& operator= (A const& src) {
     std::cout << "the assignment operator" << std::endl;
     return *this;
   }
};

void no_ref(A a) {}
void with_ref(const A & a) {}

int main()
{
    A a("my name is a");
	std::cout<<"CHKP0\n";
    A b = a;          // what is the difference
	std::cout <<"CHKP1 \n";
    A c(a);           // between these three
	std::cout <<"CHKP2 \n";
    A d;              // forms of initialization?
	std::cout <<"CHKP3 \n";
    d = a;
	std::cout <<"CHKP4 \n";
      no_ref (a);     // will this copy the value of `a`?
	std::cout <<"CHKP5 \n";
    with_ref (a);     // will this copy the value of `a`?
	std::cout <<"CHKP6 \n";

    A *aa = new A[5];
	std::cout <<"CHKPp6\n";
    delete aa;        // what will happen?
    return 0;
}
