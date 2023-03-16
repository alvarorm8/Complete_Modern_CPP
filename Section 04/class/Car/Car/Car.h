#pragma once
struct Car {
private:
	float fuel{ 0 };
	float speed{ 0 };
	int passengers{ 0 };
	int arr[5] = { 1,2,3 };
	char *p{}; //nullptr
	//char *p2 = new char{9}; // tambien se puede
	// auto no se puede usar
public:
	Car();
	Car(float amount);
	void FillFuel(float amount);
	void Accelerate();
	void Brake();
	void AddPassengers(int count); 
	void Dashboard() const; // const debe ir tanto en el .h como en .cpp
	~Car();
};
