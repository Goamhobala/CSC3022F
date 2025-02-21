## Headers and Source files
* Header files (.h) contain declarations (function prototypes, class definitions, macros etc)
* Not compiled but included in source files (.cpp) to allow the declarations to be referenced
* When compiled, the linker will then link multiple source files together, and produce an executable (a.out on Linux/MacOS, a.exe on Windows)
* If we \#include a .cpp file instead, then every source files that include it will all get a copy of those functions, resulting in multiple definition errors when linked together.
* Example:
#### add.cpp
```cpp
// add.cpp
int add(int a){
	return a + a;
}
```
#### add.h
```c++
// add.h
#ifndef ADD_H
#define ADD_H
int add(int a);
#endif
```
* The include guards directives are there to prevent multiple definition errors; even if a source files were to include add.h multiple times, the **add()** function will still only be declared once
* An alternative is using \#pragma once instead (but not all compilers support this)
#### main.cpp
```c++
#include "add.h"
#include <iostream>
int main(void){
	std::cout << "Sum: " << add(2) << std::endl;
	return 0;
}
```
* Note: <> will cause the compiler to search from a set of predefined paths that lead to system header files first, whereas "" tells the compiler to search for the .h file from within the current directory
#### compile
```
g++ -o print_2x main.cpp add.cpp
```
* Note: The compiler will compile the source files separately. The linker will then automatically link add.cpp and main.cpp together

## Directives

## Scope
* Try to avoid global variables as they can cause tricky errors
* You can force the program to ignore the local copy and use the global variable by using ::
e.g.
```cpp
int i = 5;
for (int j = 0; j < 5 ; j++ ){
	int i = j * 2;
	std::cout << ::i << std::endl;
}
```
* An **automatic variable** is a local variable that is allocated when program flow enters the scope, and deallocated when program flow leaves the scope.
e.g.
```cpp
int main(void){
	{Dog d; // automatic variable
	int c;  //automatic variable
	}
}
```

## Namespaces
* Helps the compiler figure out which source file should it look for a function/object/etc.
* Prevents naming collisions
* Can be nested
#### adder1.cpp
```cpp
namespace Adder1{
  int add(int a, int b){
  	return a + b;
  }
  namespace Return{
  	int sub(int a ,int b){
	return a - b;
	}
  }
}
```
#### adder1.h
```cpp
#ifndef ADD_H
#define ADD_H

namespace Adder1{ // namespace declaration must be inside the header file as well
  int add(int a, int b);
  namespace Return{
  	int sub(int a,int b);
  }
}
#endif
```
#### adder2.cpp
```cpp
namespace Adder2{
  int add(int a, int b){
  	return a * 2 + b * 2;
  }
}
```

#### adder2.h
```cpp
#ifndef ADD2_H
#define ADD2_H
namespace Adder2{ // namespace declaration must be inside the header file as well
  int add(int a, int b);
}
#endif```
```
#### main.cpp
```cpp
#include <iostream>
#include "adder1.h"
#include "adder2.h"
int add(int a, int b); // Forward declaration

int main(void){
	std::cout << Adder1::add(1, 2) << std::endl;
	std::cout << Adder1::Return::sub(1, 2) << std::endl;
	std::cout << Adder2::add(1, 2) << std::endl;
}

```
* You can also have unnamed namespace that is local to the current compilation unit (.cpp file)
```cpp
namespace {int a = 1;}
std::cout << a << endl;
```
* But don't mix it with the global namespace