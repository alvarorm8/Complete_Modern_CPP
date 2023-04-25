
#pragma region constexpr lambda
#include <sstream>
#include <iostream>
//////////// constexpr lambda
template<typename T, int size, typename Callback>
void ForEach(T(&arr)[size], Callback operation) {
	for (int i = 0; i < size - 1; ++i) {
		operation(arr[i]);
	}
}

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
		ForEach(taxes, [basePrice, this](float tax) {
			float taxedPrice = basePrice * tax / 100;
			price += taxedPrice;
		});
	}
	float GetPrice()const {
		return price;
	}
	auto GetDescription() {
		return [*this](const std::string& header) {
			std::ostringstream ost;
			ost << header << std::endl;
			ost << "Name : " << name << std::endl;
			ost << "Price : " << price << std::endl;
			return ost.str();
		};
		
	}
};
void UsingLambda() {
	Product *p = new Product { "Watch", 500 };
	//p.AssignFinalPrice();
	//std::cout << p.GetPrice() << std::endl;
	
	/*
	* Here we have a problem with the lambda from GetDescription.If this is passed without*, the pointer this is pointing to
	* the same location of the object p, but as we delete it, it converts into a dangling pointer and the program will crash.
	* To solve this, C++17 added the possibility to get this pointer by value, passing it with *this syntax. This way, the 
	* object is copied and no crash happens.
	*/
	auto desc = p->GetDescription() ;
	delete p ;
	std::cout << desc("##############") << std::endl;

	/*
	* C++17 introduces a new feature that if a lambda satisfies the criteria of being a constexpr expression, it automatically
	* becomes one, and the result is generated at compile time.
	*/
	auto f = [](int x,int y)/*contsexpr not necessary*/ {
		return x + y ;
	};
	constexpr auto sum = f(3,5) ; //computed at compile time
	auto sum2 = f(3,5) ; //not computed at compile time
	printf("%d", sum) ;
}
#pragma endregion