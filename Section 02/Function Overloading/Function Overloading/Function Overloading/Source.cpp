#include <iostream>
int Add(int a, int b) {
	return a + b;
}
double Add(double a, double b) {
	return a + b;
}
extern "C" void Print(int *x) {
	/*
	primitiva que se pone para poder llamar desde C u otros lenguajes a una función de C++
	Es una directiva al compilador que hace que se evite el "name mangling",
	es decir, que a cada instancia de una funcion sobrecargada se le de un nombre
	unico en la compilacion. Solo se puede poner para una instancia de una funcion
	sobrecargada.
	
	Si quiero aplicarlo a varias funciones, se haría así:

	extern "C" {
		double fun1(int a);
		int fun2(double f);
	}

	Hay que poner extern "C" tanto en la declaracion como en la definicion (.h y .cpp).
	Esto es así ya que se compilaría en el .h con un nombre y en el .cpp con otro nombre, por lo que no 
	podrá encontrar la correspondencia entre las funciones generadas.
	IMPORTANTE: SI EN EL .CPP SE INCLUYE EL .H, YA NO ES NECESARIO PONER extern "C" en el .cpp, ya que ya se incluye.

	Si queremos ver los nombres que se le asocian, podemos habilitar la creacion del archivo .map
	en Proyecto->Linker->Debugging->Generate Map File, y se puede ver en la carpeta Debug que hay a la
	altura del archivo .sln.
	*/
}
void Print(const int* x) {

}
int main() {
	using namespace std;
	int result = Add(3, 5);
	cout << result << endl;
	Add(3.1, 6.2);
	const int x = 1;
	Print(&x);
	return 0;
}