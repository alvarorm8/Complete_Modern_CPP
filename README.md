# Complete modern C++ table of contents

This document contains information about the content of the sections and solutions in the repository, so it is easier to navigate and search information.

## Section 2 - Basic language facilities

### First Program

First program. It uses cout and type traits (explained in a solution later).

### BasicIO

Basic use of std::iostream cout and cin.

### Pointers

Basic use of pointers, dereference, nullptr, etc.

### Reference

First look at references.

### Ref Vs Ptr

Advantages and disadvantages of using pointers and references.

### const Qualifier and Compound Types

Use of const keyword in functions and variables.

### auto

Use of auto keyword.

### Range-based for

Range-based for loop, with & and const usage.

### Function Overloading

Function overloading, extern "C" explanation.

### Default Function Args

Functions with default arguments. Always put as the last arguments.

### Inline functions

Explanation of inline function request to the compiler.

### Function Pointers

Use of function pointers for the first time.

### Namespace

Explanation of namespaces, with and without a name.

## Section 3 - Memory management - Part 1

### MemMgmtC

Memory management use, first with C functions malloc and free, later with new in variables and arrays. Matrix pointers (with **).

## Section 4 - Classes & Objects

### class

Basic definition of a class using a struct and its functions, use of const keyword. Explanation of default public/private members in struct/classes.

### structure

Basic use of a structure.

### Static

Use of static for a class member and initialization in .cpp file. Use of several constructors defining the logic only in one, an the others constructors call the one with the logic.

### Copy Ctor

Definition of copy constructor and move constructor in a class. Use of std::move in functions and explanation.

### Default and Deleted Functions

Use of default and delete to create and avoid creating constructors and functions in classes.

## Section 5 - Move semantics

### Lvalues and rvalues

Basic explanation of rvalues, lvalues and rvalue references.

### Move Semantics Impl

Explanation of copy and move constructors.

### RuleofFive

Explanation of rule of 5 and the members the compiler generates if we define any of the 5 members.

Explanation of copy and move elision.

Rule of 5 & 0:

*Rule of 5*

In general, if a class has resources like pointers, access to databases, sockets, etc., the following members must be defined:
1. Destructor
2. Copy Constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

*Rule of 0*

In general, if a class does not have any resources like pointers, etc., we should not implement any of the previous members.
If a member is defined, the compiler does not synthesize the other. If we don't provide any, the compiler will synthesize the
5 members.

## Section 6 - Operator overloading

### Operator Overloading

Class operators overloading as class functions, class operators overloading as global functions, use of friend keyword.

GENERAL NOTE: IF THE FIRST ARGUMENT OF THE OPERATOR IS NOT AN OBJECT OF THE CLASS (example: 5 + Integer object)
THE OPERATOR HAS TO BE DEFINED AS A GLOBAL FUNCTION, LIKE THE ONES BELOW

### UserDefConversions

Explanation of casting types, explicit keyword and Type conversion operator (to convert user defined class to primitive).

### Assignment vs Initialization

Use of Memeber Initialization List in class constructors preferred over assignment when it's possible.

## Section 7 - Memory management - Part 2

### Raw pointer

Explanation of why raw pointers in modern C++ is not recommended.

### unique_ptr

Explanation of unique_ptr smart pointer, used when we don't want to share with other parts of the code. Does not allow copy, uses move.

### shared_ptr

Explanation of shared_ptr smart pointer, used when we want to share the value of pointer with other parts of the code. Allows copy, move is not recommended.

### weak_ptr

Explanation of weak_ptr smart pointer, which point to the control block of shared_ptr to see the number of references the shared_ptr has.

### CircularRef

Explanation of a memory leak which happens with two classes with shared_ptr and solved with a weak_ptr.

### More Features

Explanation of Deleter in smart pointers, Arrays in smart pointers and Make functions (factory functions which replace new operator in modern C++).

## Section 8 - More C++ Goodies

### enums

C++11 enum class vs regular enums.

### Strings

Use of std::string class and literal types.

### StringStreams

Use of stringStreams to read and write and maintain the information in a string internally.

### UserDefinedLiterals

Definition of user defined literals.

### constexpr

Explanation of constexpr keyword from C++11, used to be evaluated at compile time.

### initializer_list

Explanation of initializer_list used for objects initialization.

### Vector

Basic use of std::vector.

### Union

Basic use of std::union.

## Section 9 - Object oriented programming

### Account

Inheritance explanation:

- Constructor inheritance with using keyword in Checking class
- Pointers to base class in Transaction class
- Virtual keyword and virtual destructor in Account class
- Upcast, Object Slicing, Downcast in main.cpp

### NewInheritanceKeywords

New C++11 keyword final, override. Abstract classes (pure virtual functions)

### Multiple inheritance

Explanation of virtual inheritance for diamong inheritance.

## Section 10 - Exception Handling

### Nested Exceptions

Basic exception handling explanation, throw function, stack unwinding explanation, nested exceptions.

### Exceptions in ctors

Exception handling and exception throw in constructors, in destructors they must never be thrown.

### ExceptionHandling-noexcept

noexcept keyword explanation.

In general, if a function calls a library function, like std::cout, we can not assure that 
function won't throw any exception, so we have to leave it as neutral.

IMPORTANT TIP: In move constructor and move assignment operator, we should mark them with 
the noexcept keyword since it will improve the performance of the code.

## Section 11 - File Input & Output

### Raw String Literals

C++11 Raw String Literal functionality explanation.

### Error Handling

Files writing and reading with std::ofstream and std::ifstream. Use of state bits (eof, good) to know the state of file reading.

### FileIO-Filecopy

Use of std::experimental::filesystem to implement a copy file functionality.

This is deprecated since in C++17 filesystem was released.

### FileIO-MoreFunctions

tellp, seekp, tellg, seekg functions.

### Binary Files

Write and read binary files.

## Section 12 - Templates

### Basics

Several basic concepts from templates are explained:

- Basic use of templates
- Template argument deduction & instantiation: the compiler deduces the type and we can force it to generate the version of a type with explicit instantiation.
- Explicit specialization: We can specialize the function logic for a certain type of variable.
- Non type template arguments: we can pass non type arguments to a template, like a number.

### Perfect Forwarding - II

Use of std::forward function to preserve the argument type of the variable passed to initialize the class members.

IMPORTANT: perfect forwarding only works with template type arguments, because it only works when argument deduction is involved

### Variadic Templates - II

Variadic templates explanation, which are functions and classes that accept an arbitrary number of arguments. These can be of any type, not all
have to be of the same type.

### Class Templates

Classes with template types in its member variables and functions.

### ClassExpSpecII

Explicit specialization of class member functions and even full classes if if is needed.

### Partial Spec

Template classes partial specialization. We can specialize a class template for a type but only specializing a part of it, like an operator, constructors/destructors, etc.

### Aliases

C++11 aliases introduced to replace typedefs. Use of templates with aliases.

### TypeTraits

Explanation of type traits, which give the ability to find the characteristics of types at compile time and transform the properties of the type.

### StaticAssert

Explanation of static_assert to evaluate expressions at compile time. Also ASSERT C macro is mentioned.

## Section 13 - Lambda expressions (C++11)

### Function Pointers

First a reference to an array is explained, which is a reference that maintains the information about the size of the array.

Second, function pointers are explained. Callbacks are defined, which can be function pointers, function objects and lambdas.

### Function Objects

Function objects are defined, which are object of a class or struct that has the function call operator overloaded.
They are more frequently implemented like structs rather than classes.

### Lambda Basics

Lambda expressions are introduced, which substitute function pointers and function objects.

### Capture List

The capture clause of lambda expressions is explained. It is used to capture variables and use them in the lambda function.

Lambda inside lambda.

### GeneralizedCapture

C++14 introduced feature explained. Allows creating features inside capture clause.

### Assignment1

Code of the assignment of the section.

## Section 14 - Standard template library

### SequenceContainers

Explanation of iterators characteristics.

Explanation of STL sequence containers:

- Arrays
- Vector
- Deque
- List
- Forward List

### AssociativeContainers

Explanation of STL associative containers:

- set, multiset
- map, multimap

### UnorderedContainers

Explanation of STL unordered containers:

- unordered_set, unordered_multiset
- unordered_map, unordered_multimap

### Algorithms

Use of several STL algorithms, there are more non seen:

- sort
- count_if
- find_if
- for_each

### ContainerChanges

Several features were added in C++11 to STL:

- emplace_back
- emplace_front
- emplace
- emplace_hint
- shrink_to_fit
- std::filesystem::file_size
- erase by value (C++20)
- find
- contains (C++20)
- extract (C++17)
- etc.

### Assignment-STL Project

Code of the assignment of the section.

## Section 15 - C++ Concurrency

### Threads

Basics of threads, like join, detach, std::ref and std::cref.

### Sharing Data

Data sharing between threads is explained using mutex and std::lock_guard. 

This solution is not recommended, the good solution is seen in Async solution.

### ThreadClass

Use of some functions in Thread class like sleep_for, native_handle, get_id, hardware_concurrency, etc.

### Async

Explanation of high level concurrency, which operates with functions instead of threads. This is done with 
the async function and std::future/std::promise classes.

### PromiseFuture

More explanations of std::future/std::promise classes and their uses for sharing data/exception between threads.

## Section 16 - C++17 Core language features

### AttributesSln

Attributes added in C++17 applied to functions and classes: nodiscard, deprecated

### FeatureMacrosSln

__has_include macro to check if a header is available 

### IfSwitchSln

C++17 introduces the capacity to define local variables inside the if and switch ().

### InlineVariablesSln

C++17 allows to initialize static variables in .h file through inline keyword. These variables can be a class member or even global variables.

constexpr static member variable is implicitly inline, so they can be initialized too.

### NestedNamespacesSln

New way to declare nested namespaces, A::B::C{} for example.

### NoExceptSln

noexcept keyword can be used in functions.

### ConstExprLambdaSln

The pointer this can be passed by value to create a copy of the object in lambda expressions.

If a lambda satisfies the criteria of being a constexpr expression, it automatically becomes one, and the result is generated at compile time

### StructuredBindingsSln

Several variables can be instantiated with elements or members of an object, which can be an object of a class/structure or an array.

### EvaluationOrderSln

Functions evaluation order was fixed.

### MandatoryCopyElisionSln

In C++17 copy elision is mandatory, even if we remove copy and move constructors.

## Section 17 - C++17 template feautures

### CTADSln

Class Template Argument Deduction in C++17 is applied also to classes, before it was only for functions.

### FoldExpressionsSln

C++17 introduces a new way of using a list of arguments with binary operators.

### TraitSuffixesSln

In C++17 a new feature was added for those type traits that return a boolean. Using _v replaces ::value.

std::is_floating_point<T>::value -> std::is_floating_point_v<T>

In C++14, a new feature was added for those type traits that perform transformations. Using _t replaces ::type.

std::remove_reference<T>::type -> std::remove_reference_t<T>

### IfConstexprSln

C++17 feature added that allows the condition of an if to be evaluated at compile time.
It discards branches of an if statement at compile time.

## Section 18 - C++17 Standard library components

### OptionalSln

std::optional is a C++17 new library type that can be used when a function may or not return a value.

### VariantSln

std::variant is a C++17 library type which is a safe replacement for union type.

std::visit and Visitors are explained to access and modify variant elements (another way of doing it).

### AnySln

std::any is introduced which can store any variable of any type in a typesafe way.

### StringViewSln

C++17 introduces string_view, which allows us to deal with character sequences without allocating memory.

### FileSystemSln

Filesystem library basic use is explained. It can be used to:

- Manipulation of filesystem path
- Create, move, rename, delete directories
- List contents of a given directory
- Get information about path, file permissions, etc.

For read & write files, we have to use stream library.

### ParallelSln

C++17 provides overloads of STL algorithms that can now execute parallelly on different threads, using a new template paremeter called execution policy.

# C++ versions

## C++11 added features

Most of features used now: 
- auto
- strcpy_s, strcpy está en desuso
- constexpr
- enum class
- std::to_string
- std::stoi
- Literal types (100u, "alvaro"s, etc.) some were added in C++14
- Definition of our own literals
- Inheritance keywords: final, override, using (Inherit all constructors of a base class)
- Destructors are implicitly noexcept(true)
- Raw String Literal
- Aliases
- static_assert
- Lambda expressions
- for_each returns a copy (copy until C++11, std::move since C++11) of the function object passed
- STL container added features: emplace_back, emplace_front, emplace, emplace_hint, shrink_to_fit, std::filesystem::file_size, find
- std::lock_guard
- C syntax to indicate a function only can throw several exceptions is deprecated in C++11 and eliminated in C++17. For example: void Foo0() throw(int, float) {}
- noexcept with variables.
- variadic templates
- Many more...

## C++14 added features

- Literal types (100u, "alvaro"s, etc.)
- if inside constexpr expressions.
- Generalized Capture
- Lambda expressions using auto to save as function.
- std::chrono_literals.
- New feature was added for those type traits that perform transformations. Using _t replaces ::type.

## C++17 added features

- Arrays for shared_ptr.
- Attributes applied to functions and classes: nodiscard, deprecated.
- __has_include macro check.
- If and switch can define local variables in the ().
- Initialization of static variables in .h file through inline keyword. These variables can be a class member or even global variables.
- constexpr static member variable is implicitly inline, so they can be initialized too.
- New way to declare nested namespaces, A::B::C{} for example.
- noexcept keyword can be used in functions.
- The pointer this can be passed by value to create a copy of the object in lambda expressions.
- If a lambda satisfies the criteria of being a constexpr expression, it automatically becomes one, and the result is generated at compile time.
- StructuredBindings: Several variables can be instantiated with elements or members of an object, which can be an object of a class/structure or an array.
- Functions evaluation order was fixed.
- Copy elision is mandatory, even if we remove copy and move constructors.
- Class Template Argument Deduction is applied also to classes, before it was only for functions.
- Fold expressions: New way of using a list of arguments with binary operators.
- New feature was added for those type traits that return a boolean. Using _v replaces ::value.
- if constexpr allows the condition of an if to be evaluated at compile time. It discards branches of an if statement at compile time.
- std::optional is a library type that can be used when a function may or not return a value.
- std::variant is a library type which is a safe replacement for union type.
- std::visit and Visitors are used to access and modify variant elements (another way of doing it).
- std::any is introduced which can store any variable of any type in a typesafe way.
- string_view allows us to deal with character sequences without allocating memory.
- Filesystem library is released. It can be used to: Manipulation of filesystem path ,Create, move, rename, delete directories ,List contents of a given directory ,Get information about path, file permissions, etc. For read & write files, we have to use stream library.
- Overloads of STL algorithms are introduced that can now execute parallelly on different threads, using a new template paremeter called execution policy.
- STL container added features: extract
- C syntax to indicate a function only can throw several exceptions is eliminated in C++17. For example: void Foo0() throw(int, float) {}


## C++20 added features

- Macros like: __cpp_capture_star_this and __cpp_inline_variables
- STL container added features: erase by value, contains
- make_shared function for arrays was added in C++20 to create a shared pointer of an array.