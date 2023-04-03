#include <iostream>
enum Colour {RED=10, GREEN, BLUE}; //normal enum
enum class Color : long{RED=5, GREEN = 10, BLUE} ; //scoped enum C++11, we can use Color:: to differentiate between Color and TrafficLight
//we can pass the type of variable we want, in this case long
void FillColor(Color color) {
	//Fill background with some color
	if(color == Color::RED) {
		//Paint with red color
		std::cout << "RED" << std::endl; 
	}
	else if(color == Color::GREEN) {
		//Paint with green color
		std::cout << "GREEN" << std::endl; 
	}
	else if(color == Color::BLUE) {
		//Paint with blue color
		std::cout << "BLUE" << std::endl; 
	}
}
enum class TrafficLight : char{RED='c', GREEN, YELLOW} ;
int main() {
	Color c = Color::RED ;
	FillColor(c) ;
	FillColor(Color::GREEN) ;
	FillColor(static_cast<Color>(2)) ;//we have to make a cast
	int x = static_cast<int>(Color::RED) ;//we have to make a cast
	return 0;
}