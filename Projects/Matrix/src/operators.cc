#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->DeleteMx();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      std::memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    this->DeleteMx();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix indices are out of range");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix indices are out of range");
  }
  return matrix_[row][col];
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}