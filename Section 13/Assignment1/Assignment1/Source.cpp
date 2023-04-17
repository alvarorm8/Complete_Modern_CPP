#include <iostream>
#include <utility>
#include <vector>
int main() {
	auto Max = [](auto x, auto y) {
		if (x > y)
			return x;
		return y;
	};

	std::cout << "Max: " << Max(6.5f, 7.0f) << std::endl;

	auto Greater = [](auto x, auto y) {
		return x > y;
	};

	std::cout << "Greater: " << Greater(6, 7) << std::endl;

	auto Less = [](auto x, auto y) {
		return x < y;
	};

	std::cout << "Less: " << Less(6.5f, 7.0f) << std::endl;

	auto MinMax = [](auto begin, auto end) {
		if (begin != end) {
			auto min = *begin;
			auto max = *begin;
			++begin;
			while (begin != end) {
				if (min > *begin)
					min = *begin;
				if (max < *begin)
					max = *begin;
				++begin;
			}
			return std::make_pair(min, max);
		}
		else {
			std::cout << "Error: begin and end iterators are the same" << std::endl;
		}
	};
	std::vector<float> vec{ 0,-10,90,-45,100 };
	auto minMax1 = MinMax(vec.begin(), vec.end());

	std::cout << "min1: " << minMax1.first << ", max1: " << minMax1.second << std::endl;

	std::vector<int> vec2{};

	auto minMax2 = MinMax(vec2.begin(), vec2.end());

	std::cout << "min2: " << minMax2.first << ", max2: " << minMax2.second << std::endl;
 }