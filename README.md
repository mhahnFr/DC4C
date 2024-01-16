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

### Final notes
This repository is licensed under the terms of the GPL 3.0.

© Copyright 2023 - 2024 [mhahnFr][1]

[1]: https://github.com/mhahnFr
