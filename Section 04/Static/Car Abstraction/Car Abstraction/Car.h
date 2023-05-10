//#pragma once
class Car {
private:
	float fuel;
	float speed;
	int passengers;
	static int totalCount;
	//the initialization of static members can't be done in constructors
	//we have to do it in a .cpp file, usually in the .cpp file of the class.
public:
	Car();
	Car(float amount);
	Car(float amount, int pass);
	~Car();
	void FillFuel(float amount);
	void Accelerate();
	void Brake();
	void AddPassengers(int count);
	void Dashboard()const;
	static void ShowCount();
};