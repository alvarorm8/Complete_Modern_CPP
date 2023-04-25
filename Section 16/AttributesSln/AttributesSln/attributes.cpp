#include <cstdlib>
#ifdef __has_include
#if __has_include(<filesystem>)
#define FS 1
#include <filesystem>
#endif
#endif


//[[deprecated("Don't use")]]
//void Foo() {
//	
//}
//
//class [[deprecated("Not allowed")]] A{
//	
//} ;
//
//namespace [[deprecated("Not allowed")]] Old{
//}

#pragma message("DO NOT USE THIS FILE")
class [[nodiscard]] Test{ //The result of every function that returns a Test type can't be ignored, no need to specify in Create() function bellow
};
[[nodiscard]]
int &Square(int x) {
	int *p = new int{x} ;
	return *p;
}
Test Create() {
	return Test{} ;
}


[[deprecated("Use the template version instead")]] //we specify not to use this method, compiler gives an error or warning with the message if we try to use it
[[nodiscard]] //we can't ignore the return value of the function. The compiler will give a warning
int * CreateIntArray(size_t size) {
	return new int[size] ;
}

template<typename T>
[[nodiscard]] T * CreateArray(size_t size) {
	return new T[size] ;
}

class [[deprecated("This class is replace by NewTest class")]] Test1 { //we can also use it with classes

};

namespace [[deprecated("Do not use")]] A {//we can also use it with namespaces


}

int main() {
	//CreateIntArray(5) ;
	//CreateArray<int>(3) ;
}
