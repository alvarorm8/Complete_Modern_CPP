#include <iostream>
//using Comparator = bool(*)(int, int);
template<typename T, int size, typename Comparator>
void Sort(T(&arr)[size], Comparator comp) {
	for (int i = 0; i < size-1; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (comp(arr[j], arr[j + 1])) {
				T temp = std::move(arr[j]);
				arr[j] = std::move(arr[j + 1]);
				arr[j + 1] = std::move(temp);
			}
		}
	}
}
bool Comp(int x, int y) {
	return x > y;
}
bool Comp1(int x, int y) {
	return x < y;
}
struct Comp2 {
	bool operator()(int x, int y) {
		return x > y;
	}
};

// In the callback, we can use a function pointer, function object or a lambda expression
template<typename T, int size, typename Callback>
void ForEach(T(&arr)[size], Callback operation) {
	for (int i = 0; i < size; ++i) {
		operation(arr[i]);
	}
}

/*
* Intenal implementation of the lambda expression used in ForEach in main.
* By default, the function operator () is a const function, which means, we
* can't modify the members of the function.
* 
* To be able to modify it, we have to remove the const specifier and, to do it,
* we have to specify the mutable keyword in the lambda expression.
*/
template<typename T>
struct __Unnamed {
	int offset;
	__Unnamed(int off) :offset(off) {

	}
	void operator()(T &x) {
		x += offset;
		++offset;
	}
};
class Product {
	std::string name;
	float price;
public:
	Product(const std::string &n, float p) :name(n), price(p) {

	}
	void AssignFinalPrice() {
		float taxes[]{ 12, 5, 5 };
		float basePrice{ price };
		//Capture this
		ForEach(taxes, [basePrice, this](float tax) { //use this pointer to capture basePrice
			float taxedPrice = basePrice * tax / 100;
			price += taxedPrice;
		});
	}
	float GetPrice()const {
		return price;
	}
};
int main() {

	// If no capture clause is not specified in a lambda, then it is automatically decomposed to a
	// function pointer, which can be used in C functions like atexit. This works using the 
	// type conversion operator mentioned in Lambda Basics solution.
	atexit([]() {
		std::cout << "Program is exitting..." << std::endl; 
	});
	Product p{ "Watch", 500 };
	p.AssignFinalPrice();
	std::cout << p.GetPrice() << std::endl;

	//Lambda within a lambda
	[](int x) {
		x *= 2;
		[](int x) {
			std::cout << x << std::endl; 
		}(x);
	}(5);
	__Unnamed<int> n(3);
	int x = 5;
	n(x);
	int arr[]{ 1,6,8,4,0 };
	ForEach(arr, [](auto x) {
		std::cout << x << " ";
	});
	std::cout << std::endl; 
	int offset = 0;

	//Here we capture in the capture list the variable offset to be able to use it in the lambda expression.
	//The variable is passed by value, which means offset inside lambda is a copy, not the variable offset outside.
	/*ForEach(arr, [offset](auto &x) {
		x += offset;
	});*/

	//IMPORTANT: the capture list only can capture variables that has already been declared. The capture list is used only
	//for local variables. Global and static variables are captured automatically.

	// If we want to modify the variable captured I have to mark it with the keyword mutable. The explanation is done
	// in the __Unnamed struct above.
	//ForEach(arr, [offset](auto &x)mutable {
	//	x += offset;
	//	++offset;
	//});

	/*
	* To capture a variable by reference: ForEach(arr, [&sum, offset](auto &x) : sum is captured by reference, offset by value
	* To capture all variables used inside the lambda by reference: ForEach(arr, [&](auto &x)
	* To capture all variables used inside the lambda by value: ForEach(arr, [=](auto &x)
	* To capture all variables used inside the lambda by reference except one: ForEach(arr, [&, offset](auto &x)
	* To capture all variables used inside the lambda by value except one: ForEach(arr, [=, &offset](auto &x)
	* With [this] we can capture all member variables if we are inside a member function. See in Product class above.
	* 
	* If we capture a variable by reference, mutable keyword is not necessary.
	*/
	int sum{};
	ForEach(arr, [&, offset](auto &x) {
		sum += x;
	});
	std::cout << "Sum:" << sum << std::endl;
	ForEach(arr, [](auto x) {
		std::cout << x << " ";
	});
	std::cout << std::endl;

	return 0;
}

void OldCode(){
	int arr[]{ 1,6,8,4,0 };
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	auto comp = [](auto x, auto y) {
		return x > y;
	};
	// We use the lambda comp in function Sort
	Sort(arr, comp);
	/*
	* We can also do it like this:
	* 
	* Sort(arr, [](auto x, auto y) {
	* 	return x > y;
	* });
	*/
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}