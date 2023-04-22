# Sugarcpp

[![CI-Linux](https://github.com/s-martin/Sugarpp/actions/workflows/ci-linux.yml/badge.svg)](https://github.com/s-martin/Sugarpp/actions/workflows/ci-linux.yml) [![CI-Windows](https://github.com/s-martin/Sugarpp/actions/workflows/ci-windows.yml/badge.svg)](https://github.com/s-martin/Sugarpp/actions/workflows/ci-windows.yml) [![CodeQL](https://github.com/s-martin/Sugarpp/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/s-martin/Sugarpp/actions/workflows/codeql-analysis.yml) [![Microsoft C++ Code Analysis](https://github.com/s-martin/Sugarpp/actions/workflows/msvc.yml/badge.svg)](https://github.com/s-martin/Sugarpp/actions/workflows/msvc.yml)

[![Coverage Status](https://coveralls.io/repos/github/s-martin/Sugarpp/badge.svg?branch=master)](https://coveralls.io/github/s-martin/Sugarpp?branch=master)

Sugarcpp is a small library, which adds syntactic sugar to C++ to make your life easier.

## Compliation

CMake is used for compilation. There are two things to build: the library and the unit tests. Here is the
short version of how to build and test everything:

### Windows

Using [vcpkg](https://github.com/microsoft/vcpkg) to install dependencies is recommended.

1. Clone or download the repository

2. Install dependencies: `vcpkg install boost-test boost-log xerces-c-dev`

#### Visual Studio 2019 or later

3. Open path in Visual Studio as CMake project.

#### Previous versions of Visual Studio

3. `md build && cd build`

4. `cmake ../ -DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/scripts/buildsystems/vcpkg.cmake`

5. Open created Visual Studio solution file in `build` directory

### Linux (Ubuntu)

1. `sudo apt install libboost-test-dev libboost-log-dev libxerces-c-dev`

If you want to use code coverage:

2. `sudo apt install lcov gcovr`

Configure and build:

3. `mkdir build && cd build`

4. `cmake ../`

5. `make`

Run unit tests:

6. `make test`

# TODO HERE

Run unit tests and create coverage:

7. `make GAlib_lcov`

8. `make GAlib_gcov`

### Building shared libraries

To build shared libraries append `-DBUILD_SHARED_LIBS:BOOL=ON` to the above `cmake`command.

See also <https://cmake.org/cmake/help/v3.15/variable/BUILD_SHARED_LIBS.html> in the CMake docs.
