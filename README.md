# globpp

globpp is a C++ template library that translates globbing patterns to a
Boost.Spirit grammar that subsequently generates a regular expression. The
latter can be used in combination with ``boost::regex`` or ``std::regex``.

## Requirements

* C++98 compiler
* Boost C++ libraries 1.55
* CMake 3.0

## Getting Started

To compile, run:

```bash
cmake -S . -B build/
cmake --build build/
```
