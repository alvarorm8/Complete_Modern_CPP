#include <iostream>
#include <typeinfo>
#include "Savings.h"
#include "Checking.h"
#include "Transaction.h"

int main()
{
	Checking ch("Bob", 100, 50);
	Transact(&ch);
	/*
	* //////////////////////////////////////////// Upcast ///////////////////////////////////////////
	* We point to a child class with a pointer or reference of the base class. The object of the child class is upcasted and we can call
	* the functions of the child class through the base class pointer or reference
	* Account * pA = &ch;
	* Account & rA = ch;
	* 
	* //////////////////////////////////////////// Object Slicing ///////////////////////////////////////////
	* We assign to an object of the base class a child object. The compiler will slice the child object to fit into a 
	* base object. We can not call the child class functions. This can also happen with a function that accepts 
	* a base class object as argument, not a pointer or reference.
	* Account acc = ch;
	* 
	* //////////////////////////////////////////// Downcast ///////////////////////////////////////////
	* The inverse can be done (assign parent object to a child class object, but in this case, we have to make it manually with a cast:
	* 
	* Checking * pChecking = static_cast<Checking*>(pA);
	* 
	* But this is dangerous since we can do this blindly and it can crash or misbehave if the object which points is not
	* the type we are casting to. To solve this, we can use typeid
	* 
	* if (typeid(*pA) == typeid(Checking))
	* 
	* Or we can use dynamic_cast, which checks first if the cast can be performed or not. If it can not be performed, 
	* it will return null, otherwise it will return the type casted pointer.
	* 
	* Checking *pChecking = dynamic_cast<Checking*>(pAccount);
	* if (pChecking != nullptr) {
	*	std::cout << "Minimum balance of Checking:" << pChecking->GetMinimumBalance() << std::endl;
	* }
	* 
	* We can use dynamic_cast with references. If the cast can not be performed, it will throw an exception of type bad cast, 
	* for example:
	* try {
	*	Checking & pChecking = dynamic_cast<Checking&>(pAccount);
	* } catch (std::exception &ex) {
	*	std::cout << "Exception: "  << ex.what() << std::endl;
	* }
	* 
	* Ideally, we should work with polymorphic use cases without knowing the type, since it's much slower using
	* dynamic_cast or typeid (typeid is faster than dynamic_cast though). Furthermore, the class will ocupy
	* more memory when we use dynamic_cast or typeid since it has to store more information in the vtable.
	* 
	* IMPORTANT: The type information is added to the class only when there is a virtual function. In this example:
	* 
		class A{
		public:
			void CallA(){}
		} ;
		class B : public A{
		} ;
		int main(){
			B b ;
			A *a = &b ;
			std::cout << typeid(*a).name() << std::endl ;
			return 0 ;
		}
	* Without type information the compiler will ascertain the type at compile-time and the type will always be A.
	*/

	return 0;
}
 
