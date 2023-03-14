#include <iostream>

/*
La palabra inline hace que el compilador sustituya la llamada a la funcion en el codigo (por ejemplo en el main cuando
se llama a Square) con el cuerpo de la funcion. Esto se hace para saltarse el overhead de la funcion, que es el tiempo 
que tarda en saltar de la llamada de la funcion al cuerpo de la misma, y volver al punto donde estaba.

Normalmente, en funciones grandes no hay problema, ya que el tiempo que tarda en la ejecucion de la funcion es mucho
mayor comparado con el overhead. Pero en funciones pequeñas que se ejecutan muy rapido, esto puede suponer un retraso
y, si es una funcion que se llama muchas veces, puede causar problemas.
*/
inline int Square(int x) {
	return x * x;
}
//#define Square(x) x*x
int main() {
	using namespace std;
	int val = 5;
	int result = Square(val + 1);
	cout << result << endl;
	return 0;
}