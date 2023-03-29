#include "Integer.h"

void Display(Integer* p) {
	if (!p) //if it is nullptr
		return;
	std::cout << p->GetValue() << std::endl;
}

Integer* GetPointer(int value) {
	Integer* obj = new Integer{value};
	return obj;
}

void Operate(int value) {
	Integer* p = GetPointer(value);
	if (p == nullptr) {
		p = new Integer{value};
	}
	p->SetValue(100);
	Display(p);
	delete p;
	p = nullptr;
	p = new Integer{};
	*p = __LINE__;
	Display(p);
	delete p;
}

int main() {
	//Writing code in modern C++ like the Operate function is not recommended since it's complicated to read and maintain. Smart pointers should be used.
	Operate(20);
	return 0;
}