# Welcome to _DC4C_!
This repository contains a few data containers written in and for the C programming language.

The name stands for **D**ata **C**ontainers **for** **C**.

## Containers
All the implemented containers come with functions to simplify the interoperability with C++ code.

In order for the function overload resolutions to work when using this library in C++ code,
make sure to include these headers before any `extern "C"` block.

### Vector
A vector similar to the `std::vector` of the C++ standard library is available. It comes with a
C++ wrapper, providing the usual constructors.

Additionally, the C++ wrapper comes with functions for the interoperability with C++'s `std::vector`.

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

## Final notes
This project is marked with CC0 1.0 Universal.

Written in 2023 - 2025 by [mhahnFr][1]

[1]: https://github.com/mhahnFr
