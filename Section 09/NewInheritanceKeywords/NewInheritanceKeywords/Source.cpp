#include <iostream>

/////////////////////////////////////////// C++11 final keyword ///////////////////////////////////////////////
/*
* We can mark a class as final if we don't want anyone inherits from it, to prevent errors. For example, if anyone inherits from Zip,
* the destructor is not virtual, so it may lead to memory leaks.
* 
* We can also mark a function with final so it is not overriden.
*/
class Zip final {
public:
	Zip() {

	}
	void Compress(const std::string &filename) {

	}
	void Decompress(const std::string &filename) {

	}
	void PrintStatistics() {

	}
	/*
	Destructor is not virtual, therefore it is risky to 
	inherit from this class.

	Zip *p = new FastZip ;
	delete p ;

	This would call Zip destructor only. Therefore, the destructor 
	of FastZip will not execute & it will not be able to release
	any resources
	*/
	~Zip() {
		//release resources
	}
};

//class FastZip : public Zip { //Cannot inherit from a final class
//
//};

/////////////////////////////////////////// C++11 Override keyword ///////////////////////////////////////////////

#pragma region Override
/*
* Abstract class: a class with at least one pure virtual function ( = 0 specifier)
* The classes which inherits from an abstract class compulsorily have to provide an implementation of 
* all pure virtual functions of the base class.
* 
* A pure virtual function can have an implementation (optionally but not usual) and it can be called
* only by derived classes.
*/
class Document {
public:
	virtual void Serialize(float version) = 0;
};
class Text : public Document {
public:
	void Serialize(float version)override final{
		std::cout << "Text::Serialize" << std::endl;
	}
};
class RichText : public Text {
public:
	//Cannot override because the function is final in base    
	/*void Serialize(float version)override {
		std::cout << "RichText::Serialize" << std::endl;
	}*/
};

/*
* In this class we try to override the Serialize function from Document, but if we declare it by error with a different argument, 
* for example:
* 
* void Serialize(int version)
* 
* The compiler will tell nothing about it (since it's not override but overload) and it can lead to bugs.
* To check the function is correctly overriden, we can mark it with the keyword override, so if anything is 
* different (like the argument), it marks it as an error. We can assure that the override is correct.
*/
class XML : public Document {
public:
	void Serialize(float version)override {
		std::cout << "XML::Serialize" << std::endl; 
	}
};

void Write(Document *p) {
	p->Serialize(1.1f);
}
#pragma endregion

int main() {
	XML xml;
	Write(&xml);
	return 0;
}