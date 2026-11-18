# Matrix

Class `Matrix` for working with rectangular matrices of real numbers in C++17: arithmetic, determinant, move and copy operations, and dynamic memory management.

## Structure

```
include/matrix.h      — class declaration
src/matrix.cpp        — class implementation
examples/example.cpp  — example of useage
```

## Requirements

Compiler with C++17 support (MSVC, g++, or clang++).

## Building and running

**Windows, Developer Command Prompt for VS** (installing with Visual Studio), in the repository folder:

```
cl /std:c++17 /EHsc /W4 /I include examples\example.cpp src\matrix.cpp /Fe:example.exe
example.exe
```

**Windows, MinGW / MSYS2:**

```
g++ -std=c++17 -Wall -Wextra -Iinclude examples/example.cpp src/matrix.cpp -o example.exe
example.exe
```

**Linux / macOS:**

```
g++ -std=c++17 -Wall -Wextra -Iinclude examples/example.cpp src/matrix.cpp -o example
./example
```

## Visual Studio:

1. Create project **Empty Project** (C++).
2. Add `src/matrix.cpp` and `examples/example.cpp`.
3. In the project properties:
   - **C/C++ → General → Additional Include Directories**: `$(ProjectDir)include`
   - **C/C++ → Language → C++ Language Standard**: `ISO C++17`

## VS Code:

Install the extension C/C++ (by Microsoft) and compile using one of the commands above in the terminal within the open repository folder.