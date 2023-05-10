#include "Car.h"
#include<iostream>
int main() {
	/*
	Por defecto, en una estructura los miembros son publicos, mientras que en una clase, por defecto son privados.
	*/
	Car c(5);
	c.Dashboard();
	c.Accelerate();

	const Car c2(5);
	c2.Dashboard();
	//c2.Accelerate(); // los objetos const solo pueden llamar a metodos const
	return 0;
}