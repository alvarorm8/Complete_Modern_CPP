//C++98 syntax to indicate this function only can throw int and float exceptions, deprecated in C`++11 and eliminated in C++17
void Foo0() throw(int, float) {
}
/*
* C++11 replaced throw with nbexcept, but it was only for variables, like this:
* void (*p)() noexcept;
*   p = Bar;
*	p() ;
* The problem is that Bar can throw an exception, so the noexcept specification does not guarantee that the function invoked won't throw
* any exception. In C++17, that would cause a compiler error, because the function pointer is noexcept but Bar is not, so now, you can define
* noexcept on the funcion you want not no throw any exception and create the function pointer without the noexcept keyword, like made in main.
*/
void Foo()noexcept{
}
void Bar(){
}

int main(){
	void (*p)() ;
	p = Foo ;
	p() ;
}