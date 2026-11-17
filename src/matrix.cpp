#pragma once

#include <matrix.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

/* Const variable for comparing double variables */
constexpr double kEpsilon = 1e-8;

void Matrix::Swap(Matrix& other) {
  /* Function of swapping variables and ptr varisbles between two matrices */
  std::swap(this->data_, other.data_);
  std::swap(this->cols_, other.cols_);
  std::swap(this->rows_, other.rows_);
}

Matrix::Matrix() {
  /* Matrix default counstructor */
  Matrix::rows_ = 0;
  Matrix::cols_ = 0;
  data_ = nullptr;
}
Matrix::Matrix(int rows, int cols) {
  /* Matrix constructor */
  Matrix::rows_ = rows;
  Matrix::cols_ = cols;
  if (Matrix::rows_ <= 0 || Matrix::cols_ <= 0) {
    Matrix::rows_ = Matrix::cols_ = 0;
  }
  data_ = new double*[rows]();
  for (int i = 0; i < rows; i++) {
    data_[i] = new double[cols]();
  }
}
Matrix::~Matrix() {
  /* Matrix destructor */
  if (data_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] data_[i];
    }
    delete[] data_;
  }
}
Matrix::Matrix(const Matrix& other) {
  /* Matrix copy constructor */
  Matrix::rows_ = other.rows_;
  Matrix::cols_ = other.cols_;
  if (Matrix::cols_ > 0 || Matrix::rows_ > 0) {
    Matrix::data_ = new double*[rows_]();
    for (int i = 0; i < Matrix::rows_; i++) {
      Matrix::data_[i] = new double[Matrix::cols_]();
      for (int j = 0; j < Matrix::cols_; j++) {
        Matrix::data_[i][j] = other.data_[i][j];
      }
    }
  } else {
    Matrix::data_ = nullptr;
  }
}
Matrix::Matrix(Matrix&& other) noexcept {
  /* Matrix move constructor */
  Matrix::Swap(other);
  other.rows_ = other.cols_ = 0;
  other.data_ = nullptr;
}
Matrix& Matrix::operator=(Matrix other) {
  /* Overloading = operator for two matrices */
  if (this != &other) {
    Matrix::Swap(other);
  }
  return *this;
}
Matrix Matrix::operator+(const Matrix& other) const {
  /* Overloading + operator for two matrices */
  if (Matrix::rows_ != other.rows_ || Matrix::cols_ != other.cols_) {
    throw std::invalid_argument("Matrix addition error");
  }
  Matrix result_mx(Matrix::rows_, Matrix::cols_);
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      result_mx.data_[i][j] = Matrix::data_[i][j] + other.data_[i][j];
    }
  }
  return result_mx;
}
Matrix Matrix::operator*(int a) {
  /* Overloading * operator for multiplying matrix by scalar */
  Matrix result_mx(Matrix::rows_, Matrix::cols_);
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      result_mx.data_[i][j] = Matrix::data_[i][j] * a;
    }
  }
  return result_mx;
}
Matrix Matrix::operator*(const Matrix& other) const {
  /* Overloading * operator for multiplying matrix by another matrix */
  if (Matrix::cols_ != other.rows_) {
    throw std::invalid_argument("Matrix multiplication error");
  }
  Matrix result_mx(Matrix::rows_, other.cols_);
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sigma = 0;
      for (int k = 0; k < other.rows_; k++) {
        sigma += Matrix::data_[i][k] * other.data_[k][j];
      }
      result_mx.data_[i][j] = sigma;
    }
  }
  return result_mx;
}
bool Matrix::operator==(const Matrix& other) const {
  /* Overloading == operator for comparing two matrices */
  if (this == &other) {
    return true;
  } else if (Matrix::rows_ != other.rows_ || Matrix::cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      if ( std::abs(Matrix::data_[i][j] - other.data_[i][j]) > kEpsilon) {
        return false;
      }
    }
  }
  return true;
}
bool Matrix::operator!=(const Matrix& other) const {
  /* Overloading != operator for comparing two matrices */
  return !(*this == other);
}
double& Matrix::operator()(int i, int j) {
  /* Overloading () operator for calling element of matrix */
  if (i >= Matrix::rows_ || j >= Matrix::cols_ || i < 0 || j < 0) {
    throw std::invalid_argument(
      "Matrix indexing error: index is out of range");
  }
  return Matrix::data_[i][j];
}
void Matrix::Transpose() {
  /* Matrix transposing method */
  Matrix new_mx(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      new_mx.data_[i][j] = Matrix::data_[j][i];
    }
  }
  Matrix::Swap(new_mx);
}
void Matrix::Print() const {
  /* Print matrix */
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << std::setprecision(4) << std::setw(8) << Matrix::data_[i][j];
    }
    std::cout << "\n";
  }
}
void Matrix::Print(int precision, int width) const {
  /* Print matrix with adjustable precision and width of column */
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << std::setprecision(precision) << std::setw(width)
                << Matrix::data_[i][j];
    }
    std::cout << "\n";
  }
}
void Matrix::SetIdentity() {
  /* Turns matrix int identity matrix */
  if (Matrix::rows_ != Matrix::cols_) {
    return;
  }
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      if (i == j) {
        Matrix::data_[i][j] = 1;
        continue;
      }
      Matrix::data_[i][j] = 0;
    }
  }
}
void Matrix::Fill(double a) {
  /* Fills all of the ... of matrix with the number a */
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      Matrix::data_[i][j] = a;
    }
  }
}
void Matrix::Fill(double func(int, int)) {
  /* Fills all of the ... of matrix woth user's function */
  /* Function uses row/column as a parameters */
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      Matrix::data_[i][j] = func(i, j);
    }
  }
}

void Matrix::FillSequence() {
  int m = 1;
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      Matrix::data_[i][j] = m++;
    }
  }
}
void Matrix::FillSequence(int step) {
  int m = 1;
  for (int i = 0; i < Matrix::rows_; i++) {
    for (int j = 0; j < Matrix::cols_; j++) {
      Matrix::data_[i][j] = m;
      m+=step;
    }
  }
}
double Matrix::CalculateDet() {
  /* Function to find determinant of matrix */
  int n = Matrix::rows_;
  if (!Matrix::GetSqr() || n == 0) {
    throw std::invalid_argument(
        "Determinant calculation error: Matrix is not square or its "
        "dimentionality equals zero.");
  } else if (n == 1) {
    return Matrix::data_[0][0];
  } else if (n == 2) {
    return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
  } else if (n <= 4) {
    /* Algorithm for calculation 3x3 and 4x4 determinant by Laplace expansion along a row */
    if (n == 3) {
      return CalcDet3x3();
    }
    double det = 0;
    /* Initializing sign lambda function (-1)^(i+j) */
    auto sign = [](int entry) { return entry % 2 == 1 ? -1 : 1; };
    for (int entry = 0; entry < n; entry++) {
      Matrix minor(3, 3);
      // Running across minor's elements: i, j - indexes for minor; big_j - index for this matrix
      for (int i = 0; i < 3; i++) {
        int big_j = 0;
        for (int j = 0; j < 3; j++, big_j++) {
          if (j == entry) {
            /* Skipping the column of this matrix that contains entry */
            big_j++;
          }
          minor(i, j) = Matrix::data_[i + 1][big_j];
        }
      }
      /* Adding the multiplication of entry and cofactor */
      det += sign(entry) * Matrix::data_[0][entry] * minor.CalcDet3x3();
    }
    return det;
  } else {
    /* Algorithm for calculation 5x5 (and bigger) determinant by Gaussian elimination */
    return Matrix::CalcDet5x5();
  }
}
int Matrix::GetRows() const {
  return Matrix::rows_;
}
int Matrix::GetCols() const {
  return Matrix::cols_;
}
bool Matrix::GetSqr() const {
  return Matrix::rows_ == Matrix::cols_;
}

double Matrix::CalcDet3x3() const {
  /* Function for calculating 3x3 determinant */
  return data_[0][0] * data_[1][1] * data_[2][2] +
         data_[0][1] * data_[1][2] * data_[2][0] +
         data_[0][2] * data_[1][0] * data_[2][1] -
         data_[0][2] * data_[1][1] * data_[2][0] -
         data_[0][0] * data_[1][2] * data_[2][1] -
         data_[0][1] * data_[1][0] * data_[2][2];
}

double Matrix::CalcDet5x5() const {
  /* Algorithm for calculation determinant more that 4x4 by Gaussian elimination */
  Matrix g = *this;
  double det = 1;
  for (int m = 0; m < g.cols_; m++) {
    for (int i = m + 1; i < g.rows_; i++) {
      if (std::abs(g(m, m)) < kEpsilon) {
        int a = g.FindNotZeroRow(i, m);
        if (!(a + 1)) {
          return 0;
        } else {
          std::swap(g.data_[m], g.data_[a]);
          det *= -1;
        }
      }
      double fac = g(i, m) / g(m, m);
      for (int j = m; j < g.cols_; j++) {
        g(i, j) = g(i, j) - g(m, j) * fac;
      }
    }
  }
  for (int i = 0; i < g.rows_; i++) {
    det *= g.data_[i][i];
  }
  return det;
}

int Matrix::FindNotZeroRow(int i, int col) const {
  /* Function for finding not zero row in Gaussian elimination */
  for (; i < Matrix::rows_; i++) {
    if (std::abs(Matrix::data_[i][col]) > kEpsilon) {
      /* Returning index of not zero row */
      return i;
    }
  }
  return -1;
}