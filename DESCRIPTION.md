Matrix - A Matrix Class in C++

## Description

The `Matrix` class implements a rectangular matrix of real numbers using dynamic memory allocation.

## Implementation Details

**Memory Management**
- A 2D array (`double**`) is allocated in the constructor and deallocated in the destructor.
- Implements the "Rule of Three": destructor, copy constructor, and copy assignment operator.
- Deep copying: each copy maintains its own buffer; modifications to one matrix do not affect others.

**Move Semantics**
- The move constructor `Matrix(Matrix&& other) noexcept` transfers ownership of the buffer without copying the underlying data. After the move, the source object enters an empty state (`rows_ == 0`, `cols_ == 0`, `data_ == nullptr`), ensuring its destructor can be called safely.
- The assignment operator `operator=(Matrix other)` accepts its parameter by value. This single operator handles both copying (from an lvalue) and moving (from an rvalue, e.g., `a = std::move(b)`). Resources are exchanged via a `swap` operation, and the old data is cleaned up by the destructor of the temporary parameter object. This follows the "copy-and-swap" idiom; there is no manual `delete` call within the assignment operator.

**Arithmetic and Access**
- `operator+` and `operator-` for matrices of identical dimensions; `operator*` for scalar multiplication and matrix-matrix multiplication.
- `operator==` and `operator!=` for comparisons, utilizing a tolerance threshold (`kEpsilon`).
- `operator()(i, j)` for accessing matrix elements, with built-in bounds checking. **Error Handling**
Throws `std::invalid_argument` in cases of incompatible dimensions, out-of-bounds indices, or negative matrix dimensions.

**Determinant**
- Sizes 1 and 2: direct formula.
- Size 3: Sarrus' rule (triangle method), constant number of operations.
- Size 4: Laplace expansion along the first row. Complexity: O(n!).
- Size 5 and larger: Gaussian elimination with partial pivoting (row swapping changes the sign of the determinant). Complexity: O(n?).

**Other Features**

- Matrix transposition.
- Creation of an identity matrix.
- Filling with a constant value or a user-defined function `f(i, j)`.
- Output with configurable precision and column width.

## Structure

include/matrix.h   - class declaration
src/matrix.cpp     - implementation
src/main.cpp       - usage example

## Panned:

- Solving systems of linear equations (Ax = b).
- Matrix inversion, rank, and concatenation (analogous to `numpy.concatenate`; `hcat`, `vcat`).