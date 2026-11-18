#pragma once

/* Const variable for comparing double variables */
//constexpr double kEpsilon = 1e-8;

class Matrix {
  // Class representing a rectangular matrix of real numbers
  //
  // Member variables:
  //  data_ - pointer to the array of matrix rows
  //  rows_ - number of rows in the matrix
  //  cols_ - number of columns in the matrix
  //
  // Features:
  //  - opitimized useage of memory (move constructors for methods is included)
  //  - writing data to the matrix and its formatted output
  //  - overloading of the multiplication operator (matr*scalar & matr*matr)
  //  - overloading of the matrix addition operator
  //  - overloading of the assignment and comparison operators
  //  - overloading of the matrix element access operator ()
  //  - method for finding the determinant
  //
  // Memory is allocated and freed by the class itself.
  // Copy and move constructors are implemented.
  // An std::invalid_argument exception is thrown for incompatible dimensions
  // in operations and out-of-bounds access.
  //
  // Determinant: for sizes 1-2, it is calculated directly; for 3 - using the
  // rule of Sarrus (triangle rule); for 4 - using cofactor (Laplace) expansion along a row;
  // for 5 and larger - by reducing to upper triangular form using Gaussian elimination
  // and taking the product of the main diagonal.

 private:
  double** data_ = nullptr;
  int rows_;
  int cols_;

 public:
  /* Function of swapping variables and ptr varisbles between two matrices */
  void Swap(Matrix& other);

  /* Matrix default counstructor */
  Matrix();

  /* Matrix constructor */
  Matrix(int rows, int cols);

  /* Matrix destructor */
  ~Matrix();

  /* Matrix copy constructor */
  Matrix(const Matrix& other);

  /* Matrix move constructor */
  Matrix(Matrix&& other) noexcept;

  /* Overloading = operator for two matrices */
  Matrix& operator=(Matrix other);

  /* Overloading + operator for two matrices */
  Matrix operator+(const Matrix& other) const;

  /* Overloading - operator for two matrices */
  Matrix operator-(const Matrix& other) const;

  /* Overloading * operator for multiplying matrix by scalar */
  Matrix operator*(int a) const;

  /* Overloading * operator for multiplying matrix by another matrix */
  Matrix operator*(const Matrix& other) const;

  /* Overloading == operator for comparing two matrices */
  bool operator==(const Matrix& other) const;

  /* Overloading != operator for comparing two matrices */
  bool operator!=(const Matrix& other) const;

  /* Overloading () operator for calling element of matrix */
  double& operator()(int i, int j);

  /* Matrix transposing method */
  void Transpose();

  /* Print matrix */
  void Print() const;

  /* Print matrix with adjustable precision and width of column */
  void Print(int precision, int width) const;

  /* Turns matrix int identity matrix */
  void SetIdentity();

  void Fill(double a);

  /* Fills all of the ... of matrix woth user's function */
  /* Function uses row/column as a parameters */
  void Fill(double func(int, int));
  
  void FillSequence();
  void FillSequence(int step);

  /* Function to find determinant of matrix */
  double CalculateDet();

  int  GetRows() const;
  int  GetCols() const;
  bool GetSqr() const;

 private:
  /* Function for calculating 3x3 determinant */
  double CalcDet3x3() const;

  /* Algorithm for calculation determinant more that 4x4 by Gaussian elimination */
  double CalcDet5x5() const;

  /* Function for finding not zero row in Gaussian elimination */
  int FindNotZeroRow(int i, int col) const;
};