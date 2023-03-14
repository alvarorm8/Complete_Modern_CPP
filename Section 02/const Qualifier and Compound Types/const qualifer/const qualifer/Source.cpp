#include <iostream>
void Print(int *ptr) {
	using namespace std;
	cout << *ptr << endl;
}
void UsingConst() {
	using namespace std;
	float radius = 0;
	cin >> radius;
	const float PI = 3.14159f;
	float area = PI * radius * radius;
	float circumference = PI * 2 * radius;
	cout << "Area is : " << area << endl;
	cout << "Circumference is : " << circumference << endl;

	// <tipo de variable a la que apunta> * <tipo de puntero> <nombre>= ...
	// const int * ptr = &CHUNK_SIZE -> apunta a un const int por lo que no puede cambiar el valor de dicha variable
	// aunque apunte a una variable que no es constante
	// int * const ptr = &x -> apunta a un int, no se puede cambiar la dirección de memoria a la que apunta
	// const int * const ptr = &x -> apunta a un const int y no se puede cambiar la dirección a la que apunta
	const int CHUNK_SIZE = 512;
	const int * ptr = &CHUNK_SIZE;
	//*ptr = 1;
	int x = 10;
	//ptr = &x;
	//*ptr = 1;
	Print(&x);
	cout << "main->x" << x << endl;
}

void PrintRef(const int &ref) {
	using namespace std;
	cout << ref << endl;
}
void UsingConstRef() {
	int x = 5;
	PrintRef(1); //para poder pasar un valor a la función, hay que poner en la declaración de la función el argumento como const
}
int main() {
	UsingConst();
	UsingConstRef();
	
	return 0;
}














