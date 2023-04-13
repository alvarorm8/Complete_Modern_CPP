#pragma once
#include <utility>

namespace Assignment1 {

	//The declaration and definition happen in header file. Templates generally do not use .h and .cpp structure.

	template<typename T>
	T Add(T x, T y) {
		return x + y;
	}

	template<typename T>
	T ArraySum(const T* x, size_t arrSize) {
		T sum = 0;
		for (int i = 0; i < arrSize; ++i) {
			sum += x[i];
		}
		return sum;
	}

	template<typename T>
	T Max(const T* x, size_t arrSize) {
		if (arrSize < 1) {
			return -1;
		}
		T max = x[0];
		for (int i = 1; i < arrSize; ++i) {
			if (x[i] > max)
				max = x[i];
		}
		return max;
	}

	template<typename T>
	std::pair<T, T> MinMax(const T* pArr, size_t arrSize)
	{
		if (arrSize < 2) {
			return std::pair<T, T>{-1, -1};
		}
		std::pair<T, T> minMax{ pArr[0] < pArr[1] ? pArr[0] : pArr[1] , pArr[0] < pArr[1] ? pArr[1] : pArr[0] };
		for (int i = 2; i < arrSize; ++i) {
			if (minMax.first < pArr[i])
				minMax.first = pArr[i];

			if (minMax.second > pArr[i])
				minMax.second = pArr[i];
		}
		return minMax;
	}
}
