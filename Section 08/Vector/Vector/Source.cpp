#include <iostream>
#include <vector>
int main() {
	int arr[10];
	int *ptr = new int[10];
	for (int i = 0; i < 10; ++i) {
		ptr[i] = i * 10;
	}

	std::vector<int> data{ 1,2,3 };
	for (int i = 0; i < 5; ++i) {
		data.push_back(i * 10);
	}
	//Access
	data[0] = 100;
 	//	std::cout << data[i] << " ";
	//}
	for (auto x : data) {
		std::cout << x << " ";
	}
	auto it = data.begin();
	//std::cout << *it;
	++it;

	--it;
	it = it + 5; //jump 5 positions
	//*it = 20 //we have write access too
	//Delete
	it = data.begin();
	data.erase(it); //delete position it
	std::cout << std::endl;
	for (auto x : data) {
		std::cout << x << " ";
	}
	//Insert
	it = data.begin() + 5;
	data.insert(it, 500); //insert position at it value
	std::cout << std::endl;
	for (auto x : data) {
		std::cout << x << " ";
	}
	return 0;
}