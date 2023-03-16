#include <iostream>
class Integer {
	int m_Value{ 0 };
public:
	// Se usa default para solicitar al compilador que cree un constructor por defecto, un destructor, constructor copia y operador asignacion
	Integer() = default;
	//Integer() {
	//	m_Value = 0;
	//}
	Integer(int value) {
		m_Value = value;
	}
	// Con delete podemos indicar al compilador que no cree el constructor copia. 
	// Se puede usar con cualquier funcion, como el caso de abajo, en el que dejamos
	// que se pase un entero, pero no un float
	Integer(const Integer &) = delete;
	void SetValue(int value) {
		m_Value = value;
	}
	void SetValue(float) = delete;
};

int main() { 
	Integer i1; 
	i1.SetValue(5);
	//Error as SetValue(float) is deleted
	i1.SetValue(67.1f);
	return 0;
}