#include "s21_matrix_oop.h"

void S21Matrix::Create() {
  matrix_ = new double *[this->rows_]();
  for (int i = 0; i < this->rows_; i++) {
    matrix_[i] = new double[this->cols_]();
  }
}

void S21Matrix::Remove() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::Copy(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  Create();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix() {
  rows_ = cols_ = 1;
  Create();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::out_of_range("Rows/Cols should be great 0");
  rows_ = rows;
  cols_ = cols;
  Create();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  Create();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() { Remove(); }

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::out_of_range("Incorrect input");
  S21Matrix result(rows, cols_);
  for (int i = 0; i < result.rows_; i++)
    for (int j = 0; j < result.cols_; j++)
      if (i < rows_) result.matrix_[i][j] = matrix_[i][j];
  *this = result;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::out_of_range("Incorrect input");
  S21Matrix result(rows_, cols);
  for (int i = 0; i < result.rows_; i++)
    for (int j = 0; j < result.cols_; j++)
      if (i < cols_) result.matrix_[i][j] = matrix_[i][j];
  *this = result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if ((cols_ == other.cols_) && (rows_ == other.rows_)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_ && result; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          result = false;
          break;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Invalid input! Matrices have different sizes");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Invalid input! Matrices have different sizes");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "Invalid input! Columns matrix A should be equal rows matrix B");
  S21Matrix buf(*this);
  SetCols(other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
      for (int k = 0; k < buf.cols_; k++) {
        matrix_[i][j] += buf.matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}
S21Matrix S21Matrix::MinorMatrix(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int n = 0, m = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        minor.matrix_[n][m] = matrix_[i][j];
        m++;
        if (m == rows_ - 1) {
          m = 0;
          n++;
        }
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_)
    throw std::invalid_argument("Invalid input!  Matrix  should be square");
  double result;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    if (rows_ == 2) {
      result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
    } else {
      for (int i = 0; i < rows_; i++) {
        S21Matrix buf(MinorMatrix(0, i));
        result += pow((-1), i) * matrix_[0][i] * buf.Determinant();
        buf.Remove();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_)
    throw std::invalid_argument("Invalid input!  Matrix  should be square");
  S21Matrix result(rows_, rows_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[i][j] =
            pow((-1), i + j) * MinorMatrix(i, j).Determinant();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (fabs(Determinant()) < EPS)
    throw std::invalid_argument("Error!  Determinant is 0");
  S21Matrix comp(CalcComplements());
  S21Matrix result(comp.Transpose());
  result.MulNumber(1.0 / Determinant());
  comp.Remove();
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  if (matrix_ != other.matrix_) {
    Remove();
    Copy(other);
  }
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    Remove();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("index is out of range");
  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("index is out of range");
  return matrix_[row][col];
}
