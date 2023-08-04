#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

const double EPS = 1e-6;

class S21Matrix {
 public:
  //  constructors and destructors
  S21Matrix();   // Default constructor
  ~S21Matrix();  // Destructor
  S21Matrix(int rows, int cols);  // Параметризированный конструктор с
                                  // количеством строк и столбцов
  S21Matrix(const S21Matrix &other);  // Конструктор копирования
  S21Matrix(S21Matrix &&other);  // Конструктор переноса

  // matrix methods
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // перегрузка операторов
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix operator=(const S21Matrix &other);
  S21Matrix operator=(S21Matrix &&other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  double &operator()(int row, int col);
  double operator()(int row, int col) const;

  // accessors & mutators
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated

  //  additional functions
  void Create();
  void Remove();
  void Copy(const S21Matrix &other);
  S21Matrix MinorMatrix(int row, int col) const;
};

#endif  // S21_MATRIX_OOP_H_
