#include <stdio.h>
#include <stdlib.h>
#include <iostream>
void Malloc() {
	//int *p = (int*)calloc(5, sizeof(int)); // igual que malloc pero inicia la memoria a 0
	int *p = (int*)malloc(5 * sizeof(int)); // en C++ hay que hacer el cast al tipo de puntero, por defecto es void*, en C lo hace automaticamente
	if (p == NULL) {
		printf("Failed to allocate memory\n");
		return;
	}
	*p = 5;
	printf("%d", *p);
	free(p);
	p = NULL; // se asigna null al puntero ya que al hacer el free, pasa a ser un dangling pointer y no se debe trabajar con el
	//free(p);
}

void New() {
	int *p = new int(5); // si falla al reservar la memoria, da una excepcion
	//int* p = new int{ 5 }; // Para inicializarlo, se puede hacer con uniform initialization
	*p = 6;
	std::cout << *p << std::endl;
	delete p;
	p = nullptr; //obviamente, la asignacion a null debe hacerse si el puntero tiene la oportunidad de seguir usandose, si acaba la funcion
	// y se pierde la variable, no tiene sentido hacerlo
}
void NewArrays() {
	int* p = new int[5];
	//int* p = new int[5]{10}; //valor inicial todos igual
	//int* p = new int[5]{1,2,3,4,5}; //valor inicial 
	for (int i = 0; i < 5; ++i) {
		p[i] = i;
	}
	delete[]p;
}
void Strings() {
	char *p = new char[4]; //es importante reservar 1 byte mas para el operador nulo (\n)
	strcpy_s(p, 4, "C++"); // strcpy_s añade el caracter nulo automaticamente, strcpy en C++11 esta en desuso
	std::cout << p << std::endl;
	delete[]p;
}
void TwoD() {
	int *p1 = new int[3];
	int *p2 = new int[3];

	int **pData = new int *[2]; //int **pData es un puntero a puntero, que representa un array de punteros
	pData[0] = p1;
	pData[1] = p2;

	pData[0][1] = 2;

	// Es importante liberar la memoria en el orden que la reservamos

	delete[]p1;//delete []pData[0] otra manera
	delete[]p2;//delete []pData[1] otra manera

	delete [] pData;
}
int main() {
	int data[2][3] = {
		1,2,3,
		4,5,6
	}; //1,2,3,4,5,6
	   //data[0][1]
	Strings();



	return 0;
}