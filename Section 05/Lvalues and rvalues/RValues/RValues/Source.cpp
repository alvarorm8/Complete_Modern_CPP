#include <iostream>

//Returns r-value, it returns a value
int Add(int x, int y) {
	return x + y;
}
//Return l-value, it returns a reference
int & Transform(int &x) {
	x *= x;
	return x;
}

void Print(int &x) {
	std::cout << "Print(int&)" << std::endl; 
}
void Print(const int &x) {
	std::cout << "Print(const int&)" << std::endl;

}
void Print(int &&x) {
	std::cout << "Print(int &&)" << std::endl;
}
int main() {
	// La utilidad de los r-values es para detectar valores temporales y expresiones.
	//x is lvalue
	int x = 10;
	//int& ref3 = 19; //can not bind a temporary value (such as r-value variable)
	const int& ref3 = 19; //it is allowed if the reference is constant
	//ref is l-value reference
	int &ref = x ;
	//Transform returns an l-value
	int &ref2 = Transform(x) ;
	//Binds to function that accepts l-value reference, the first one
	Print(x);
	

	//rv is r-value reference
	int &&rv = 8 ;
	
	//Add returns a temporary (r-value)
	int &&rv2 = Add(3,5) ;

	//int&& rv3 = x; error, can not bind a persistent value (such as l-value variable)
	//Binds to function that accepts a temporary, i.e. r-value reference, the third one
	Print(3);
	return 0;
}

