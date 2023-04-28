#include <chrono>
#include <iostream>
#include <random>
#include <string_view>
#include <vector>
#include <execution>
/*
* By default STL algorithms execute serially
* C++17 provides overloads to these algorithms that can now execute parallelly on different threads and at the same time
* Algorithms that can be parallelized accept a new template paremeter called execution policy, used to disambiguate the calls to
* overloads of the algorithm
* 
* Syntax:
* 
* std::algorithm(execution_policy, begin, end...)
* 
* Execution policies exist in execution header and in std::execution namespace.
* 
* sequenced_policy - seq: algorithms will be executed sequentially. Same as invoking algorithms in C++14
* parallel_policy - par: algorithms should be executed parallelly. It may create new threads or use threads from a thread pool 
* parallel_unsequenced_policy - par_unseq: algorithms execution may be parallelized, vectorized (multiple instructions can be executed in pararell)
* or migrated accross threads.
* 
* There is a huge list of parallelized algorithms which can be seen in slide 226 of the ppt. They already exist before C++17, but in this version they were parallelized.
* There are new ones added in C++17, seen in slide 227 of ppt.
* 
* Should we always use parallel versions?
* 
* Parallel algorithms have some overhead, which is the initialization cost (threads and preparing data) to be executed parallelly.
* So sometimes the overhead causes the sequential algorithm is faster than the parallelized version.
* 
* For example, in the sort algorithms used below, if the size of the vector is too small, like 100 elements, the performance in the 
* sequential algorithm is faster. If it is of size 1000000 for example, the parallel version will be faster.
* 
* Parallel algorithms can use both input and output iterators, but there's a limitation with the type of iterators that can be used.
* 
* Some algorithms can not be parallelized, for example, shuffle, binary search, max, min, etc.
* 
* Certain algorithms may require synchronization, and this is expensive, so it can degrade the performance.
* 
* For Exceptions:
* 
* In parallel algorithms, internal functions of the elements being operated are called. If an exception is thrown in one of those functions 
* and it is not handled, the algorithm will call call std::terminate to end the program.
* This also happens if sequential execution policy is chosen.
* 
* This is not applicable to sequential algorithms, they do not call terminate and you can handle the exception. So if your elements being processed
* can throw an exception, use sequential algorithm instead.
* 
* Parallel algorithms may throw std::bad_alloc if they fail to acquire memory needed for execution.
* 
* So the answer the question is: you have to do tests of your data set and see which algorithm is better, and take into account the considerations
* said above.
*/

//Helper class to see performance differences
class Timer {
	std::chrono::steady_clock::time_point m_start ;
public:
	Timer():m_start{std::chrono::steady_clock::now()} {
		
	}
	void ShowResult(std::string_view message = "") {
		auto end = std::chrono::steady_clock::now() ;
		auto difference = end - m_start ;
		std::cout << message
			<< ':'
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count()
			<< '\n' ;
	}

	void setStartTime() {
		m_start = std::chrono::steady_clock::now();
	}
};
constexpr unsigned VEC_SIZE{100} ;
std::vector<long> CreateVector() {
	std::vector<long> vec ;
	vec.reserve(VEC_SIZE) ;
	std::default_random_engine engine{std::random_device{}()} ;//random_device provides a random initialization value to the default_random_engine
	std::uniform_int_distribution<long> dist{0, VEC_SIZE} ;
	for(unsigned i = 0 ; i < VEC_SIZE ; ++i) {
		vec.push_back(dist(engine)) ;
	}
	return vec ;
}
int main() {
	auto dataset = CreateVector() ;
	Timer t ;
	//Parallel and non-parallel version of sort
	std::sort(dataset.begin(), dataset.end()) ;
	t.ShowResult("Sorting time sequential");

	t.setStartTime();
	std::sort(std::execution::par, dataset.begin(), dataset.end()) ;
	t.ShowResult("Sorting time parallel");
	//The difference is 126 ms vs 29 ms
	

	//Parallel and non-parallel version of accumulate
	t.setStartTime();
	auto result = std::accumulate(dataset.begin(), dataset.end(),0L) ;
	t.ShowResult("Accumulate time sequential");

	t.setStartTime();
	auto result = std::reduce(dataset.begin(), dataset.end(),0L) ; //There is no parallel version of accumulate, reduce is the new parallel algorithm, but the implementation is different
	t.ShowResult("Reduce time parallel");
	//The difference is 26 microseconds vs 100 nanoseconds
}

