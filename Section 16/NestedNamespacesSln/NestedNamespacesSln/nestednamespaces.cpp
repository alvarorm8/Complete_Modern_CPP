#include <iostream>
//Usual way to nest namespaces
namespace A{
	namespace B{
		namespace C{
		}
	}
}

//C++17 new way to nest namespaces
namespace A::B::C{
	void Foo(){
	}
	void Foo1() {
	}
	void Foo2() {
	}
}

int main(){
	//Ways to access the functions
	A::B::C::Foo() ;
	using A::B::C::Foo1 ;
	Foo1();
	using namespace A::B::C ;
	Foo2() ;
}