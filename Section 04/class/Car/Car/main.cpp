#include "Car.h"
#include<iostream>
int main() {
	Car c(5);
	c.Dashboard();
	c.Accelerate();

	const Car c2(5);
	c2.Dashboard();
	//c2.Accelerate(); // los objetos const solo pueden llamar a metodos const
	return 0;
}