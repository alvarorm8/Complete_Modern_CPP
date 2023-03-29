#include "integer.h"
#include <memory>
// unique_ptr is used when we don't want to share with other parts of the code
void Display(Integer *p) {
	if(!p) {
		return ;
	}
	std::cout << p->GetValue() << std::endl; 
}
Integer *GetPointer(int value) {
	Integer *p = new Integer{value} ;
	return p ;
}
void Store(std::unique_ptr<Integer> &p) { // the pass by reference is necessary since a copy of the unique_ptr can not be done
	std::cout << "Storing data into a file:" << p->GetValue() << std::endl; 
}
void Operate(int value) {
	std::unique_ptr<Integer> p{GetPointer(value)} ;
	if(p == nullptr) {
		//p = new Integer{value} ;
		p.reset(new Integer{value}) ; // if the smart pointer holds a pointer, it will delete it first, and then assign to the new pointer
	}
	p->SetValue(100) ;
	Display(p.get()) ;
	//delete p ;
	//p = nullptr ; //valid, but with reset it's done automatically
	//p = new Integer{} ;
	p.reset(new Integer{}) ;
	*p = __LINE__ ;
	Display(p.get()) ;
	Store(p) ;//instead of passing by reference, we can move the pointer into the function argument with std::move function, but we have to reset it after the call
	//delete p ;
}
int main() {
	Operate(5) ;
}