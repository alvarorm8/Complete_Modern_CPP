#include <iostream>
/*
* Before C++17, this code evalution was unpredictable, we did not know how the compiler would evaluate them:
* 
* std::cout << a() << b() << c() ; This expands to:
*
* std::cout.operator<<(a()).operator<<(b()).operator<<(c));
*                      ^^^             ^^^            ^^^
*                       1               2              3
* ^^^^^^^^^^^^^^^^^^^^^^^^^ ^^^^^^^^^^^^^^^ ^^^^^^^^^^^^^^
*            4                     5               6
* There are 6 function calls in total, which invocation order we don't know: it could be 3,2,1 or 1,2,3
* This can cause a problem when memory allocation is invoked, for example.
* 
* In C++17, this was fixed. The compiler prohibits interleaving between subexpressions.
* In the example below, prior C++17, the compiler could evaluate 2,1,4,3,  1,2,3,4, etc.
* Now, as interleaving subexpressions is prohibited, the order can be: 1,3,2,4 or 2,4,1,3.
*
* This way, if in the first function passed as parameter there's memory allocation for example, this memory can't be 
* leaked if an error on the second function passed as paremeter happens.
*/

class EvaluationOrder {
public:
	EvaluationOrder& First(int) {
		std::cout << __FUNCSIG__ << std::endl; //__FUNCSIG__ name of the function
		return *this;
	}
	EvaluationOrder& Second(int) {
		std::cout << __FUNCSIG__ << std::endl;
		return *this;
	}
};
int FirstSubExpression(int) {
	std::cout << __FUNCSIG__ << std::endl;
	return 0 ;

}
int SecondSubExpression(int) {
	std::cout << __FUNCSIG__ << std::endl;
	return 0 ;

}
int main() {
	EvaluationOrder eo ;
	eo.First(FirstSubExpression(0)).Second(SecondSubExpression(0)) ;
//           *********************         **********************
// 	                   1                              2
//     **************************** ******************************
//                    3                               4

/*
* C++14 evaluation:
* 
* int __cdecl SecondSubExpression(int)
* int __cdecl FirstSubExpression(int)
* class EvaluationOrder &__cdecl EvaluationOrder::First(int)
* class EvaluationOrder &__cdecl EvaluationOrder::Second(int)
* 
* The order is: 2,1,3,4. The order could have been another.
* 
* C++17 evaluation: 
* 
* int __cdecl FirstSubExpression(int)
* class EvaluationOrder &__cdecl EvaluationOrder::First(int)
* int __cdecl SecondSubExpression(int)
* class EvaluationOrder &__cdecl EvaluationOrder::Second(int)
* 
* The order is: 1,3,2,4. Could have been 2,4,1,3
*/
} 

