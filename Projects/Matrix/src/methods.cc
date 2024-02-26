#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  this->matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_]();
    std::memcpy(matrix_[i], other.matrix_[i], other.cols_ * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { this->DeleteMx(); }