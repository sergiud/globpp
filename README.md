# globpp

![Linux](https://github.com/sergiud/globpp/actions/workflows/linux.yml/badge.svg)
![Windows](https://github.com/sergiud/globpp/actions/workflows/windows.yml/badge.svg)
[![codecov](https://codecov.io/gh/sergiud/globpp/branch/master/graph/badge.svg?token=F5KTQRZVPS)](https://codecov.io/gh/sergiud/globpp)

globpp is a C++ template library that translates globbing patterns to a
Boost.Spirit grammar that subsequently generates a regular expression. The
latter can be used in combination with ``boost::regex`` or ``std::regex``.

## Requirements

* C++11 compiler
* Boost C++ libraries 1.55
* CMake 3.0

## Getting Started

To compile, run:

```bash
cmake -S . -B build/
cmake --build build/
```
