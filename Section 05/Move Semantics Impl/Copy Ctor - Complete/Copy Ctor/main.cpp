#include "Integer.h"
#include <iostream>

Integer Add(const Integer &a, const Integer &b){
	Integer temp ;
	temp.SetValue(a.GetValue() + b.GetValue()) ;
	return temp;
}
int main() {
	Integer a(1), b(3) ;
	a.SetValue(Add(a,b).GetValue()) ; 
	/*
	Aqui en lugar de llamarse al constructor copia (que copiaría del objeto temp de la función Add al objeto temporal al que se accede en la línea 11 al hacer el getValue), 
	se llama al constructor de movimiento (que mueve los recursos de temp a ese objeto temporal al que se accede en getValue), por lo que es más rápido y ocupa menos recursos.
	*/
	return 0;
}