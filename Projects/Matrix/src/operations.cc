#include "s21_matrix_oop.h"

static int IsEq(double A, double B) { return std::fabs(A - B) <= s21_EPS; }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_ && result; i++) {
      for (int j = 0; j < cols_ && result; j++) {
        result = IsEq(matrix_[i][j], other.matrix_[i][j]);
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        ;
      }
    }
  } else {
    throw std::invalid_argument("Different matrix dimensions.");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        ;
      }
    }
  } else {
    throw std::invalid_argument("Different matrix dimensions.");
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ == other.rows_) {
    double res = 0;
    S21Matrix tmpMx(rows_, other.cols_);
    int max_k = cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < max_k; k++) {
          res += matrix_[i][k] * other.matrix_[k][j];
        }
        tmpMx.matrix_[i][j] = res;
        res = 0;
      }
    }
    *this = (std::move(tmpMx));
  } else {
    throw std::invalid_argument("Different matrix dimensions.");
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmpMx(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmpMx.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmpMx;
}

double S21Matrix::Determinant() {
  if (rows_ == cols_) {
    double det = 1.0;
    S21Matrix cpyMx(*this);
    for (int i = 0; i < cpyMx.rows_; i++) {
      int pivot_row = i;
      for (int j = i + 1; j < cpyMx.rows_; j++) {
        if (std::abs(cpyMx.matrix_[j][i]) >
            std::abs(cpyMx.matrix_[pivot_row][i])) {
          pivot_row = j;
        }
      }
      if (pivot_row != i) {
        std::swap(cpyMx.matrix_[i], cpyMx.matrix_[pivot_row]);
        det *= -1;
      }
      for (int j = i + 1; j < cpyMx.rows_; j++) {
        double ratio = 0;
        if (cpyMx.matrix_[i][i] != 0) {
          ratio = cpyMx.matrix_[j][i] / cpyMx.matrix_[i][i];
        }
        for (int k = i; k < cpyMx.cols_; k++) {
          cpyMx.matrix_[j][k] -= ratio * cpyMx.matrix_[i][k];
        }
      }
    }

    for (int i = 0; i < cpyMx.rows_; i++) {
      det *= cpyMx.matrix_[i][i];
    }
    return det;
  } else {
    throw std::invalid_argument("The matrix is not square.");
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ == cols_) {
    S21Matrix tmpMx(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        double minor = 0;
        S21Matrix reducedMx = this->ReduceMatrixSize(i, j);
        minor = reducedMx.Determinant();
        tmpMx.matrix_[i][j] = pow(-1, (i + j)) * minor;
      }
    }
    return tmpMx;
  } else {
    throw std::invalid_argument("The matrix is not square.");
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det != 0) {
    S21Matrix tmpMx = this->CalcComplements();
    S21Matrix resultMx = tmpMx.Transpose();
    resultMx.MulNumber((double)1 / det);
    return resultMx;
  } else {
    throw std::invalid_argument("Calculation error.");
  }
}