#include <iostream>
#include <variant>
#include <string>

/*
* C++17 library type.
* It is a safe replacement for union type.
* 
* Members of variant are destroyed properly, unlike union, where we have to destroy them manually.
* 
* The first member is always default initialized, but you can initialize other members in constructor.
* 
* It is strange since variant always has a value, but if it does not, it will throw a std::bad_variant_access 
* on invalid access. The same happens if you try to acces an inactive member.
*/
struct Number {
	int m_Num{} ;
	Number(int num): m_Num{num} {
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number() {
		std::cout << __FUNCSIG__ << std::endl;
	}
	~Number() {
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number(const Number& other) {
		m_Num = other.m_Num ;
		
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number(Number&& other) noexcept {
		m_Num = other.m_Num ;
		other.m_Num = 0 ;
		std::cout << __FUNCSIG__ << std::endl;
	}

	Number& operator=(const Number& other) {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other){
			return *this;
		}
		m_Num = other.m_Num ;
		
		return *this;
	}

	Number& operator=(Number&& other) noexcept {
		std::cout << __FUNCSIG__ << std::endl;
		if (this == &other)
			return *this;
		m_Num = other.m_Num ;
		other.m_Num = 0 ;
		
		return *this;
	}
		friend std::ostream& operator <<(std::ostream &out, const Number &n) {
		return out << n.m_Num ;
	}
};

struct Visitor {
	//All operators are const, since they do not modify the state of the Visitor object
	void operator()(const std::string &s)const {
		std::cout << "string:" <<  s << std::endl; 
		
	}
	void operator()(int x)const {
		std::cout << "int:" << x << std::endl ;
	}
	void operator()(const Number &n)const {
		std::cout << "Number:" << n << std::endl; 
		
	}
};
struct Modifier {
	//All operators are const, since they do not modify the state of the Visitor object
	void operator()( std::string &s)const {
		s += " modified string" ;
	}
	void operator()(int& x)const {
		x += 1000 ;
	}
	void operator()( Number &n)const {
		n = 999 ;
	}
};
int main() {
	using namespace std::string_literals ;
	try {
		////////////////////////// Basic operations ////////////////////
		std::cout << "<<<<<<<<<<< Basic operations >>>>>>>>>>>" << std::endl;
		std::variant<std::string, int, Number> v1; //default initializes the first member, the second is not initialized
		std::variant<std::string, int, Number> v{ 7 }; //initializes the second member, the first is not initialized

		auto val = std::get<int>(v); //read from variable type, returns a reference to it
		val = std::get<1>(v); //read from index, returns a reference to it

		//If we pass to get an index which does not exist or a type which the variant does not have, the code won't compile

		auto activeIndex = v.index(); //returns index of the active member

		auto p = std::get_if<int>(&v); //returns a pointer to the element of the type. If the type does not exist, the code won't compile
		auto p2 = std::get_if<1>(&v); //returns a pointer to the element of the type. If the index does not exist, the code won't compile
		//If we pass an index or type which is not active, it does not throw any exception, it returns nullptr value
		if (p == nullptr) {
			std::cout << "Not active\n";
		}
		else {
			std::cout << *p << std::endl;
		}
		////////////////////////// Assignment of the variant to a new variable //////////////////////////
		std::cout << "<<<<<<<<<<< Assignment of the variant to a new variable >>>>>>>>>>>" << std::endl;
		v = Number{1} ;
		v.emplace<Number>(100) ;//to emplace we pass the arguments to the constructor of the variable type
		std::get<Number>(v) = 100 ;
		//std::get returns by reference, we can modify the value through it, but for it to work, the variable must be initialized, if 
		//the variant has another variable initialized, for example, string, this would throw an exception, since the reference to the
		//Number element does not exist

		/*
		* Another way of accessing is through visitation. 
		* 
		* In visitation, we use the function visit, to which we have to pass a visitor. A visitor is a class that provides function call
		* operators for each possible type. These objects are passed to the visit function, which invokes each operator for each type inside
		* the variant, depending on which type is initialized.
		* 
		* In the function operator, you can read or write the value in the variant.
		* 
		* The class Visitor above has the three operators to access string, int and Number, as our variant example has those types.
		* 
		* The class Modifier is another visitor which modifies the values of the variant.
		* 
		* We can also use a lambda expression as a visitor
		*/

		std::cout << "############### Assignment using visitors ###############" << std::endl;
		v1 = 7;
		std::visit(Visitor(), v1);
		v1 = "C++";
		std::visit(Visitor(), v1);
		v1.emplace<Number>(100);
		std::visit(Visitor(), v1);

		v1 = 7;
		std::visit(Modifier{}, v1) ;
		std::visit(Visitor{}, v1) ;
		
		v1 = "C++" ;
		std::visit(Modifier{}, v1) ;
		std::visit(Visitor{}, v1) ;

		v1.emplace<Number>(100) ;
		std::visit(Modifier{}, v1) ;
		std::visit(Visitor{}, v1) ;

		std::cout << "############### Assignment using a lambda ###############" << std::endl;

		auto visitor = [](auto &x) {
			using T = std::decay_t<decltype(x)> ; //decltype with int returns a reference, and we want the basic type, that's why we use decay_t
			if constexpr (std::is_same_v<T, int>){
				std::cout << "int : " << x << std::endl; 
			}else if constexpr (std::is_same_v<T, std::string>){
				std::cout << "string:" << x << std::endl; 
			}else if constexpr(std::is_same_v<T, Number>){
				std::cout << "Number:" << x << std::endl ;
			}
		} ;

		v = "using lambda";
		std::visit(visitor,v) ;

		v = 555 ;
		std::visit(visitor,v) ;

		v = Number{3} ;
		std::visit(visitor,v) ;

	}
	catch (std::exception& ex) {
		std::cout << "Exception:" << ex.what() << std::endl;
	}
}
