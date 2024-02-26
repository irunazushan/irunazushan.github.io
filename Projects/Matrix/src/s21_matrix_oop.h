#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cmath>
#include <cstring>
#include <iostream>

#define s21_EPS 1e-7

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // overload operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);

  // methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // help func
  void Print();
  int getRows();
  int getCols();
  double getNum(int row, int col);
  void DeleteMx();
  S21Matrix& setRows(int rows);
  S21Matrix& setCols(int rows);
  S21Matrix& setNum(int row, int col, double num);
  void SetMatrix(int num);
  S21Matrix ReduceMatrixSize(int del_i, int del_j);

 private:
  int rows_, cols_;
  double** matrix_;
};

#endif