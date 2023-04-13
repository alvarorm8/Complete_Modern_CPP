#pragma once
#include <utility>

namespace Assignment3 {

	//Modify the functions of Assignment1.h to accept a reference to an array using non-type template arguments
	//The declaration and definition happen in header file. Templates generally do not use .h and .cpp structure.

	template<typename T>
	T Add(T x, T y) {
		return x + y;
	}

	template<typename T, int size>
	T ArraySum(T(&arr)[size]) {
		T sum = 0;
		for (int i = 0; i < size; ++i) {
			sum += arr[i];
		}
		return sum;
	}

	template<typename T, int size>
	T Max(T(&arr)[size]) {
		if (size < 1) {
			return -1;
		}
		T max = arr[0];
		for (int i = 1; i < size; ++i) {
			if (arr[i] > max)
				max = arr[i];
		}
		return max;
	}

	template<typename T, int size>
	std::pair<T, T> MinMax(T(&arr)[size])
	{
		if (size < 2) {
			return std::pair<T, T>{-1, -1};
		}
		std::pair<T, T> minMax{ arr[0] < arr[1] ? arr[0] : arr[1] , arr[0] < arr[1] ? arr[1] : arr[0] };
		for (int i = 2; i < size; ++i) {
			if (minMax.first < arr[i])
				minMax.first = arr[i];

			if (minMax.second > arr[i])
				minMax.second = arr[i];
		}
		return minMax;
	}
}
#pragma once
