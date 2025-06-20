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

## Pair
The implementation of the pair has been inspired by the standard pair of the C++ programming language ([`std::pair`][7]).

### C usage
To use it, simply include its header [`pair.h`][8] and use the functions created by the macros defined within.  
**Example** usage:
```c
// main.c

#include <pair.h>

typedef_pair(int, char);
typedef_pair_named(/* name:  */ int_string, 
                   /* type1: */ int,
                   /* type2: */ const char*);

int main(void) {
    pair_int_char_t pairIntChar = { .first = 1, .second = 'A' };
    
    pairIntChar = make_pair_int_char(2, 'B');
    
    pair_int_string_t pairIntString = { .first = 4, .second = "DC4C" };
    
    pairIntString = make_pair_int_string(11, "Hello World");
}
```

#### Standard conformance
The C implementation adheres to the C90 standard.

### C++ usage
When compiled within C++ code, additional interoperability functions are available, as demonstrated below:
```c++
// main.cpp

#include <pair.h>

typedef_pair(int, char);
typedef_pair_named(int_string, int, const char*);

int main() {
    pair_int_char_t pairIntChar = { 1, 'A' };
    
    std::pair<int, char> cppPairIntChar = dc4c::to_cpp(pairIntChar);
    
    
    pair_int_string_t pairIntString = make_pair_int_string(4, "DC4C");
    
    std::pair<int, const char*> cppPair = std::make_pair(11, "Hello World");
    
    pairIntString = dc4c::to_dc4c(cppPair);
}
```

#### Standard conformance
The C++ interoperability adheres to the C++98 standard.

## Optional
The implementation of the optional has been inspired by the standard optional of the C++ programming language ([`std::optional`][9]).

### C usage
To use it, simply include its header [`optional.h`][10] and use the functions created by the macros defined within.  
**Example** usage:
```c
// main.c

#include <optional.h>

#include <stdio.h> // For printf(...)

typedef_optional(int);
typedef_optional_named(/* name: */ string,
                       /* type: */ const char*);

int main(void) {
    optional_int_t optInt = { .has_value = false };

    optional_string_t optStr = { .has_value = true, .value = "DC4C" };
    if (optStr.has_value) {
        printf("%s\n", optStr.value);
    }
}
```

#### Standard conformance
The C implementation conforms to the C90 standard.

### C++ usage
When compiled within C++ code, additional interoperability functions are available, as shown below:
```c++
// main.cpp

#include <optional.h>

typedef_optional(int);
typedef_optional_named(string, const char*);

int main() {
    optional_int_t optInt = { true, 123 };

    std::optional<int> cppOptInt = dc4c::to_cpp(optInt);

    std::optional<const char*> cppOptStr = std::make_optional("DC4C");

    optional_string_t optStr = dc4c::to_dc4c(cppOptStr);
}
```

#### Standard conformance
The C++ interoperability adheres to the C++17 standard.

## Final notes
This project is marked with CC0 1.0 Universal.

Written in 2023 - 2025 by [mhahnFr][1]

[1]: https://github.com/mhahnFr
[2]: https://en.cppreference.com/w/cpp/container/vector.html
[3]: DC4C/vector.h
[4]: DC4C/vector.hpp
[5]: https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html
[6]: https://gcc.gnu.org/onlinedocs/gcc/Typeof.html
[7]: https://en.cppreference.com/w/cpp/utility/pair.html
[8]: DC4C/pair.h
[9]: https://en.cppreference.com/w/cpp/utility/optional.html
[10]: DC4C/optional.h