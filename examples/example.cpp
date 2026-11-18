#include <iostream>
#include <stdexcept>
#include <utility>
#include "matrix.h"

// Functions for Fill(func)
double DiagonalTwo(int i, int j) { return i == j ? 2.0 : 0.0; }
double RowPlusCol(int i, int j) { return i + j; }

void Title(const char* text) {
  std::cout << "\n==== " << text << " ====\n";
}

int main() {
  // 1. Constructors and dimensions
  Title("1. Constructors and dimensions");
  Matrix empty;
  std::cout << "Default matrix: " << empty.GetRows() << "x" << empty.GetCols() << "\n";

  Matrix a(2, 3);
  std::cout << "Matrix(2,3) square? " << (a.GetSqr() ? "yes" : "no") << "\n";

  Matrix zero_size(0, 5);
  std::cout << "Matrix(0,5): " << zero_size.GetRows() << "x" << zero_size.GetCols() << "\n";

  // 2. Filling methods
  Title("2. Filling methods");
  a.Fill(7.5);
  std::cout << "Fill(7.5):\n";
  a.Print();

  a.Fill(RowPlusCol);
  std::cout << "Fill(RowPlusCol):\n";
  a.Print();

  a.FillSequence();
  std::cout << "FillSequence():\n";
  a.Print();

  a.FillSequence(3);
  std::cout << "FillSequence(3):\n";
  a.Print();

  // 3. Printing with formatting
  Title("3. Print formats");
  a.Print();
  std::cout << "Print(2, 6):\n";
  a.Print(2, 6);

  // 4. Element access with ()
  Title("4. Element access operator()");
  a(1, 2) = 100;
  std::cout << "a(1,2) after assignment: " << a(1, 2) << "\n";
  try {
    a(5, 5) = 1;
  } catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << "\n";
  }

  // 5. SetIdentity
  Title("5. SetIdentity");
  Matrix id(3, 3);
  id.SetIdentity();
  std::cout << "Identity 3x3:\n";
  id.Print();

  Matrix rect(2, 3);
  rect.SetIdentity();
  std::cout << "SetIdentity on non-square 2x3 (unchanged):\n";
  rect.Print();

  // 6. Transpose
  Title("6. Transpose");
  Matrix t = a;
  std::cout << "Before transpose (" << t.GetRows() << "x" << t.GetCols() << "):\n";
  t.Print();
  t.Transpose();
  std::cout << "After transpose (" << t.GetRows() << "x" << t.GetCols() << "):\n";
  t.Print();

  // 7. Arithmetic operators
  Title("7. Arithmetic operators");
  Matrix b = a;
  b.Transpose();  // b is 3x2

  Matrix sum = a + a;
  std::cout << "a + a:\n";
  sum.Print();

  Matrix diff = a - a;
  std::cout << "a - a:\n";
  diff.Print();

  Matrix scaled = a * 3;
  std::cout << "a * 3:\n";
  scaled.Print();

  Matrix product = a * b;  // 2x3 * 3x2 = 2x2
  std::cout << "a * b (2x3 * 3x2):\n";
  product.Print();

  try {
    Matrix bad = a + b;
  } catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << "\n";
  }

  try {
    Matrix bad = a * a;  // 2x3 * 2x3 is not allowed
  } catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << "\n";
  }

  // 8. Comparison operators
  Title("8. Comparison operators");
  Matrix same = a;
  std::cout << "a == same: " << (a == same ? "true" : "false") << "\n";
  std::cout << "a != same: " << (a != same ? "true" : "false") << "\n";
  std::cout << "a == b: " << (a == b ? "true" : "false") << "\n";
  std::cout << "a != b: " << (a != b ? "true" : "false") << "\n";

  // 9. Determinant
  Title("9. Determinant");

  Matrix m1(1, 1);
  m1(0, 0) = 5;
  std::cout << "det 1x1 (expected 5): " << m1.CalculateDet() << "\n";

  Matrix m2(2, 2);
  m2(0, 0) = 4; m2(0, 1) = 7;
  m2(1, 0) = 2; m2(1, 1) = 6;
  std::cout << "det 2x2 (expected 10): " << m2.CalculateDet() << "\n";

  Matrix m3(3, 3);
  m3(0, 0) = 2; m3(0, 1) = 0; m3(0, 2) = 1;
  m3(1, 0) = 3; m3(1, 1) = 1; m3(1, 2) = 0;
  m3(2, 0) = 1; m3(2, 1) = 2; m3(2, 2) = 4;
  std::cout << "det 3x3 (expected 13): " << m3.CalculateDet() << "\n";

  Matrix m4(4, 4);
  m4.Fill(DiagonalTwo);
  std::cout << "det 4x4 diagonal of 2 (expected 16): " << m4.CalculateDet() << "\n";

  Matrix m5(5, 5);
  m5.Fill(DiagonalTwo);
  std::cout << "det 5x5 diagonal of 2 (expected 32): " << m5.CalculateDet() << "\n";

  try {
    Matrix rect_det(2, 3);
    rect_det.CalculateDet();
  } catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << "\n";
  }

  // 10. Copy, move, assignment, swap
  Title("10. Copy, move, assignment, swap");

  Matrix copy_mx = a;
  std::cout << "Copy constructor, copy_mx == a: " << (copy_mx == a ? "true" : "false") << "\n";

  Matrix moved = std::move(copy_mx);
  std::cout << "After move, moved == a: " << (moved == a ? "true" : "false") << "\n";
  std::cout << "After move, copy_mx size: " << copy_mx.GetRows() << "x" << copy_mx.GetCols() << "\n";

  Matrix assigned(1, 1);
  assigned = a;
  std::cout << "Assignment, assigned == a: " << (assigned == a ? "true" : "false") << "\n";

  Matrix x(1, 1);
  Matrix y(3, 3);
  y.SetIdentity();
  x.Swap(y);
  std::cout << "After Swap, x size: " << x.GetRows() << "x" << x.GetCols() << "\n";
  x.Print();
  std::cout << "After Swap, y size: " << y.GetRows() << "x" << y.GetCols() << "\n";

  int pre_exit_val;
  std::cin >> pre_exit_val;

  return 0;
}