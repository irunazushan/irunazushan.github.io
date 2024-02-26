#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using namespace std;

struct MethodsTest : public testing::Test {
  S21Matrix *mx;

  void SetUp() {
    mx = new S21Matrix(3, 3);
    mx->setNum(0, 0, 7);
    mx->setNum(0, 1, 2);
    mx->setNum(0, 2, -3);
    mx->setNum(1, 0, 8);
    mx->setNum(1, 1, 4);
    mx->setNum(1, 2, 13);
    mx->setNum(2, 0, 0);
    mx->setNum(2, 1, -4);
    mx->setNum(2, 2, 2);
  }
  void TearDown() { delete mx; }
};

TEST_F(MethodsTest, mutatorTest_1) {
  mx->setCols(2);
  mx->setRows(2);
  mx->setCols(5);
  mx->setRows(5);
  ASSERT_EQ(mx->getNum(3, 3), 0);
}

TEST_F(MethodsTest, mutatorTest_2) {
  mx->setNum(2, 1, 123654);
  ASSERT_EQ(mx->getNum(2, 1), 123654);
}

TEST_F(MethodsTest, accessorTest_1) { ASSERT_EQ(mx->getNum(2, 1), -4); }

TEST_F(MethodsTest, accessorTest_2) { ASSERT_EQ(mx->getRows(), 3); }

TEST_F(MethodsTest, accessorTest_3) { ASSERT_EQ(mx->getCols(), 3); }

TEST_F(MethodsTest, constructorTest_1) {
  S21Matrix mx0;
  ASSERT_EQ(mx0.getCols(), 0);
  S21Matrix mx1(2, 7);
  ASSERT_EQ(mx1.getRows(), 2);
  ASSERT_EQ(mx1.getCols(), 7);
  S21Matrix copyMx(*mx);
  ASSERT_EQ(copyMx.getNum(1, 2), 13);
}

TEST_F(MethodsTest, constructorTest_2) {
  S21Matrix moveMx(std::move(*mx));
  ASSERT_EQ(moveMx.getNum(1, 2), 13);
  ASSERT_EQ(mx->getRows(), 0);
}

struct OperatorsTest : public testing::Test {
  S21Matrix *mx1;
  S21Matrix *mx2;

  void SetUp() {
    mx1 = new S21Matrix(3, 3);
    mx1->setNum(0, 0, 7);
    mx1->setNum(0, 1, 2);
    mx1->setNum(0, 2, -3);
    mx1->setNum(1, 0, 8);
    mx1->setNum(1, 1, 4);
    mx1->setNum(1, 2, 13);
    mx1->setNum(2, 0, 0);
    mx1->setNum(2, 1, -4);
    mx1->setNum(2, 2, 2);
    mx2 = new S21Matrix(3, 3);
    mx2->setNum(0, 0, 9);
    mx2->setNum(0, 1, 7);
    mx2->setNum(0, 2, 5);
    mx2->setNum(1, 0, -9);
    mx2->setNum(1, 1, 2);
    mx2->setNum(1, 2, 0);
    mx2->setNum(2, 0, 13);
    mx2->setNum(2, 1, 3);
    mx2->setNum(2, 2, -5);
  }
  void TearDown() {
    delete mx1;
    delete mx2;
  }
};

TEST(OperatorsTest_, parenthesisTest_1) {
  S21Matrix mx(10, 4);
  mx(9, 3) = 3;
  ASSERT_EQ(mx(9, 3), 3);
  mx(9, 3) = 6;
  ASSERT_NE(mx(9, 3), 3);
}

TEST(OperatorsTest_, parenthesisTest_2) {
  S21Matrix mx(5, 4);
  int isError = 0;
  try {
    mx(7, 7);
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST(OperatorsTest_, parenthesisTest_3) {
  const S21Matrix mx(10, 4);
  ASSERT_EQ(mx(9, 3), 0);
}

TEST(OperatorsTest_, parenthesisTest_4) {
  const S21Matrix mx(5, 4);
  int isError = 0;
  try {
    mx(7, 7);
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST_F(OperatorsTest, SumTest_1) {
  *mx1 += *mx1 + (*mx2 + *mx2);
  ASSERT_EQ(mx1->getNum(1, 1), 12);
}

TEST_F(OperatorsTest, SumTest_2) {
  S21Matrix mx(4, 10);
  int isError = 0;
  try {
    *mx1 += mx;
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST_F(OperatorsTest, SubTest_1) {
  *mx1 -= *mx1 + (*mx1 - *mx2);
  ASSERT_EQ(mx1->getNum(2, 1), 7);
}

TEST_F(OperatorsTest, SubTest_2) {
  S21Matrix mx(4, 10);
  int isError = 0;
  try {
    *mx1 -= mx;
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST_F(OperatorsTest, MulNumTest_1) {
  *mx1 *= 10;
  ASSERT_EQ(mx1->getNum(2, 1), -40);
}

TEST_F(OperatorsTest, MulNumTest_2) {
  *mx2 *= *mx1 * 7;
  ASSERT_EQ(mx2->getNum(2, 0), 805);
}

TEST_F(OperatorsTest, MulMatrixTest_1) {
  *mx1 *= (*mx1 * *mx2);
  ASSERT_EQ(mx1->getNum(2, 0), -696);
}

TEST_F(OperatorsTest, MulMatrixTest_2) {
  *mx2 *= ((*mx1 * *mx2) * *mx2 * *mx1);
  ASSERT_EQ(mx2->getNum(1, 2), 21274);
}

TEST_F(OperatorsTest, MulMatrixTest_3) {
  S21Matrix mx(4, 10);
  int isError = 0;
  try {
    *mx1 *= mx;
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST_F(OperatorsTest, AssignmentTest_1) {
  S21Matrix moveMx = *mx1;
  ASSERT_EQ(moveMx.getNum(1, 2), 13);
  ASSERT_EQ(mx1->getRows(), 3);
}

TEST_F(OperatorsTest, AssignmentTest_2) {
  S21Matrix moveMx = std::move(*mx1);
  ASSERT_EQ(moveMx.getNum(1, 2), 13);
  ASSERT_EQ(mx1->getRows(), 0);
}

TEST_F(OperatorsTest, EqualTest_1) { ASSERT_EQ(*mx1 == *mx2, 0); }

TEST_F(OperatorsTest, EqualTest_2) {
  S21Matrix copyMx(*mx1);
  ASSERT_EQ(copyMx == *mx1, 1);
}

TEST_F(OperatorsTest, EqualTest_3) { ASSERT_EQ(mx1->EqMatrix(*mx2), 0); }

TEST_F(OperatorsTest, EqualTest_4) {
  S21Matrix mx3(7, 8);
  ASSERT_EQ(*mx1 == mx3, 0);
}

struct OperationsTest : public testing::Test {
  S21Matrix *mx;

  void SetUp() {
    mx = new S21Matrix(3, 3);
    mx->setNum(0, 0, 7);
    mx->setNum(0, 1, 2);
    mx->setNum(0, 2, -3);
    mx->setNum(1, 0, 8);
    mx->setNum(1, 1, 4);
    mx->setNum(1, 2, 13);
    mx->setNum(2, 0, 0);
    mx->setNum(2, 1, -4);
    mx->setNum(2, 2, 2);
  }
  void TearDown() { delete mx; }
};

TEST(OperationsTest_, transposeTest_1) {
  S21Matrix mx(1, 10);
  S21Matrix transposedMx = mx.Transpose();
  ASSERT_EQ(transposedMx.getRows(), 10);
  ASSERT_EQ(transposedMx.getCols(), 1);
}

TEST_F(OperationsTest, DeterminanteTest_1) {
  double det = mx->Determinant();
  ASSERT_EQ(det, 484);
}

TEST(OperationsTest_, DeterminanteTest_1) {
  S21Matrix mx(1, 1);
  mx.setNum(0, 0, 25);
  double det = mx.Determinant();
  ASSERT_EQ(det, 25);
}

TEST(OperationsTest_, DeterminanteTest_2) {
  S21Matrix mx(4, 10);
  double det = 999;
  try {
    det = mx.Determinant();
  } catch (...) {
    det = 0;
  }
  ASSERT_EQ(det, 0);
}

TEST_F(OperationsTest, Complements_Test_1) {
  S21Matrix compMx = mx->CalcComplements();
  ASSERT_EQ(compMx(0, 0), 60);
  ASSERT_EQ(compMx(1, 2), 28);
  ASSERT_EQ(compMx(2, 1), -115);
}

TEST(OperationsTest_, Complements_Test_2) {
  S21Matrix mx(4, 10);
  mx.SetMatrix(10);
  double isError = 0;
  try {
    S21Matrix compMx = mx.CalcComplements();
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST_F(OperationsTest, Inverse_Test_1) {
  S21Matrix inverseMx = mx->InverseMatrix();
  inverseMx.Print();
  S21Matrix unitMx = *mx * inverseMx;
  ASSERT_EQ(unitMx(0, 0), 1);
  ASSERT_EQ(unitMx(1, 1), 1);
  ASSERT_EQ(unitMx(2, 2), 1);
}

TEST(OperationsTest_, Inverse_Test_2) {
  S21Matrix mx(4, 10);
  mx.SetMatrix(10);
  double isError = 0;
  try {
    S21Matrix inverseMx = mx.InverseMatrix();
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

TEST(OperationsTest_, Inverse_Test_3) {
  S21Matrix mx(2, 2);
  double isError = 0;
  try {
    S21Matrix inverseMx = mx.InverseMatrix();
  } catch (...) {
    isError = 1;
  }
  ASSERT_EQ(isError, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}