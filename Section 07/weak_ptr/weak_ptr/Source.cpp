#include <iostream>
/*
* Weak pointer are a type of pointers that points to the control block of shared pointers. This means it points to the
* number of references that the shared pointer has (the function use_count()). Therefore, there can be several weak pointers
* pointing to the same control block of several shared pointers.
* 
* When a shared pointer is destroyed, its control block is decremented by one, reaching 0 when the last shared pointer is destroyed,
* and then the memory is released. In this case, the control block is 0. The control block will not be destroyed while
* there are weak pointers pointing to it. So even if there are no shared pointers, we can access the control block through weak pointers.
* 
* We can access the control block through the function expired, if it's 0 it returns true, if not, it returns false. If it's true, there are
* no more shared pointers, so the memory is unaccesible. If it's false, we can access the underlying shared pointer through the weak pointer, 
* and for that, we have to call lock, which will return a new shared pointer, incrementing the control block by 1. When we are done with the 
* shared pointer obtained from lock, it will be destroyed and decrement the control block and, if it becomes 0, release the memory.
*/
class Printer {
	std::weak_ptr<int> m_pValue{} ;
public:
	void SetValue(std::weak_ptr<int> p) {
		m_pValue = p ;
	}
	void Print() {
		if(m_pValue.expired()) {
			std::cout << "Resource is no longer available" << std::endl;
			return ;
		}
		auto sp = m_pValue.lock() ;
		std::cout << "Value is:" << *sp << std::endl ;
		std::cout << "Ref count:" << sp.use_count() << std::endl ;
		//here sp is destroyed, and the control block of the shared pointers decrements by one
	}
};
int main() {
	Printer prn ;
	int num{} ;
	std::cin >> num ;
	std::shared_ptr<int> p{new int{num}} ;
	prn.SetValue(p) ;
	if(*p > 10) {
		p = nullptr ;
	}
	prn.Print() ;
}