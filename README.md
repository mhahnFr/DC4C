# DC4C - *D*ata *C*ontainers *for C*
This project aims to add some standard data containers to the C programming language. All of them are compatible
with the C++ programming language and allow a seamless interaction between the two programming languages.

## Vector
The implementation of the vector has been inspired by the standard vector of the C++ programming language ([`std::vector`][2]).

### C usage
To use it, simply include its header [`vector.h`][3] and use the macros defined within.  
**Example** usage:
```c
// main.c

#include <vector.h>

#include <stdio.h> // For printf(...)

typedef_vector(int);

typedef_vector_named(/* name: */ string, 
                     /* type: */ const char*);

int main(void) {
    vector_int_t    intVector = vector_initializer;
    vector_string_t stringVector = vector_initializer;
    
    vector_push_back(&stringVector, "Hello");
    vector_insert(&intVector, 1, /* position: */ 0);
    
    printf("%s\n", vector_erase(&stringVector, 0));
    
    vector_push_back(&stringVector, "Hello");
    vector_push_back(&stringVector, "DC4C");
    
    vector_forEach(&intVector, elem, {
        printf("%d\n", *elem);
    });
    vector_iterate(&stringVector, {
        printf("%s ", *element);
    });
    printf("\n");
    
    vector_destroy(&intVector);
    vector_destroy(&stringVector);
}
```

#### Standard conformance
The C implementation conforms to the C99 standard except for the usage of expression statements, [which are a GNU extension][5]
and the usage of the `typeof` operator, which is part of the C23 standard or available as [GNU extension][6].

### C++ usage
If used within C++ code, the [wrapper class][4] is automatically available.  
**Example** usage:
```c++
// main.cpp

#include <vector.h>

#include <iostream> // For std::cout ...

typedef_vector(int);
typedef_vector_named(string, const char*);

extern "C" void c_function(vector_int_t* vec) {}

void cpp_function(const std::vector<int>& vec) {}

int main() {
    dc4c::vector_int    vecInt;
    dc4c::vector_string vecStr;
    
    vecInt.insert(123, 0);
    vecInt.push_back(-1);
    
    vecStr.push_back("Hello");
    vecStr.push_back("DC4C");
    
    vecInt.sort();
    for (const auto& elem : vecInt) {
        std::cout << elem << std::endl;
    }
    c_function(vecInt);   // Implicit conversion to and from the C vector type
    cpp_function(vecInt); // Implicit conversion to and from the std::vector
        
    for (const auto& elem : vecStr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // The wrapper uses RAII, therefor it is destructed automatically
}
```

#### Standard conformance
The C++ wrapper class conforms to the C++11 standard.

---
# Welcome to _DC4C_!
This repository contains a few data containers written in and for the C programming language.

The name stands for **D**ata **C**ontainers **for** **C**.

## Containers
All the implemented containers come with functions to simplify the interoperability with C++ code.

In order for the function overload resolutions to work when using this library in C++ code,
make sure to include these headers before any `extern "C"` block.

### Optional
An optional similar to the `std::optional` of the C++17 standard library is available.

### Pair
A pair similar to the `std::pair` of the C++ standard library is available.

## Standard compliance
All containers are compatible with the C90 and C++98 standards, respectively, unless noted otherwise.

### Vector
The C implementation requires the C99 standard, the C++ implementation the C++11 standard.

### Optional
The interoperability with C++17's `std::optional` is only available when compiled with the C++17 (or newer) standard.

---

## Final notes
This project is marked with CC0 1.0 Universal.

Written in 2023 - 2025 by [mhahnFr][1]

[1]: https://github.com/mhahnFr
[2]: https://en.cppreference.com/w/cpp/container/vector.html
[3]: DC4C/vector.h
[4]: DC4C/vector.hpp
[5]: https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html
[6]: https://gcc.gnu.org/onlinedocs/gcc/Typeof.html