#include "s21_matrix_oop.h"

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

double S21Matrix::getNum(int row, int col) { return this->matrix_[row][col]; }

S21Matrix& S21Matrix::setRows(int rows) {
  S21Matrix cpyMx(*this);
  this->DeleteMx();
  S21Matrix resizedMx(rows, cpyMx.cols_);
  double maxRow = cpyMx.rows_;
  if (rows < maxRow) {
    maxRow = rows;
  }
  for (int i = 0; i < maxRow; i++) {
    std::memcpy(resizedMx.matrix_[i], cpyMx.matrix_[i],
                cpyMx.cols_ * sizeof(double));
  }
  *this = resizedMx;
  return *this;
}

S21Matrix& S21Matrix::setCols(int cols) {
  S21Matrix cpyMx(*this);
  this->DeleteMx();
  S21Matrix resizedMx(cpyMx.rows_, cols);
  double maxCol = cpyMx.cols_;
  if (cols < maxCol) {
    maxCol = cols;
  }
  for (int i = 0; i < cpyMx.rows_; i++) {
    std::memcpy(resizedMx.matrix_[i], cpyMx.matrix_[i],
                maxCol * sizeof(double));
  }
  *this = resizedMx;
  return *this;
}

S21Matrix& S21Matrix::setNum(int row, int col, double num) {
  this->matrix_[row][col] = num;
  return *this;
}

void S21Matrix::Print() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("|%9.3lf| ", matrix_[i][j]);
    }
    printf("\n");
  }
}

void S21Matrix::SetMatrix(int num) {
  srand(time(NULL));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = -num + rand() % (2 * num + 1);
    }
  }
}

S21Matrix S21Matrix::ReduceMatrixSize(int del_i, int del_j) {
  S21Matrix reducedMx(rows_ - 1, cols_ - 1);
  int k = -1, l = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != del_i) k++;
    for (int j = 0; j < cols_; j++) {
      if (i != del_i && j != del_j) {
        reducedMx.matrix_[k][l++] = matrix_[i][j];
      }
    }
    l = 0;
  }
  return reducedMx;
}

void S21Matrix::DeleteMx() {
  if (this->matrix_ != NULL) {
    for (int i = 0; i < rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
  }
  this->matrix_ = NULL;
}