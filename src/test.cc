#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(ConstructorDestructor, Default) {
  S21Matrix a1;
  S21Matrix a2(1, 1);
  EXPECT_TRUE(a1(0, 0) == 0.0);
  EXPECT_TRUE(a1 == a2);
}
TEST(ConstructorDestructor, Params1) {
  S21Matrix a(3, 5);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetCols(), 5);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_TRUE(a(i, j) == 0.0);
    }
  }
}

TEST(ConstructorDestructor, Params2) {
  EXPECT_THROW(S21Matrix a(0, 0), std::out_of_range);
}

TEST(ConstructorDestructor, Params3) {
  EXPECT_THROW(S21Matrix a(-2, 2), std::out_of_range);
}

TEST(ConstructorDestructor, Copy) {
  S21Matrix a(2, 2);
  a(0, 0) = 2.0;
  a(0, 1) = 0.1;
  a(1, 0) = 10;
  a(1, 1) = -4.2;
  S21Matrix a2(a);
  EXPECT_EQ(a.GetRows(), a2.GetRows());
  EXPECT_EQ(a.GetCols(), a2.GetCols());
  EXPECT_EQ(a(0, 0), a2(0, 0));
  EXPECT_EQ(a(0, 1), a2(0, 1));
  EXPECT_EQ(a(1, 0), a2(1, 0));
  EXPECT_EQ(a(1, 1), a2(1, 1));
}

TEST(ConstructorDestructor, Move) {
  S21Matrix a(2, 2);
  a(0, 0) = 2.0;
  a(0, 1) = 0.1;
  a(1, 0) = 10;
  a(1, 1) = -4.2;
  S21Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), 2);
  EXPECT_EQ(b.GetCols(), 2);
  EXPECT_EQ(b(0, 0), 2.0);
  EXPECT_EQ(b(0, 1), 0.1);
  EXPECT_EQ(b(1, 0), 10);
  EXPECT_EQ(b(1, 1), -4.2);
}

TEST(ConstructorDestructor, Destructor) {
  S21Matrix a(3, 4);
  a.~S21Matrix();
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
}

TEST(GettersAndSetters, GetRowsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetRows(), 3);
}

TEST(GettersAndSetters, GetColsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetCols(), 4);
}

TEST(GettersAndSetters, SetRows1) {
  S21Matrix a(1, 1);
  a(0, 0) = 9;
  a.SetRows(2);
  ASSERT_FLOAT_EQ(9, a(0, 0));
  ASSERT_FLOAT_EQ(0, a(1, 0));
}

TEST(GettersAndSetters, SetRows2) {
  S21Matrix a(4, 3);
  a.SetRows(3);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_FALSE(a.GetRows() == 4);
}

TEST(GettersAndSetters, SetRows3) {
  S21Matrix a(1, 1);
  EXPECT_THROW(a.SetRows(-3), std::out_of_range);
}

TEST(GettersAndSetters, SetCols1) {
  S21Matrix a(1, 1);
  a(0, 0) = 9;
  a.SetCols(3);
  ASSERT_FLOAT_EQ(9, a(0, 0));
  ASSERT_FLOAT_EQ(0, a(0, 2));
}

TEST(GettersAndSetters, SetCols2) {
  S21Matrix a(3, 4);
  a.SetCols(3);
  EXPECT_EQ(a.GetCols(), 3);
  EXPECT_FALSE(a.GetCols() == 4);
}

TEST(GettersAndSetters, SetCols3) {
  S21Matrix a(1, 1);
  EXPECT_THROW(a.SetCols(-3), std::out_of_range);
}

TEST(Operators, Plus1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -2.4;
  b(0, 1) = 0;
  b(1, 0) = 14.2;
  b(1, 1) = 100;
  c(0, 0) = 0;
  c(0, 1) = 5;
  c(1, 0) = 13.2;
  c(1, 1) = 200;
  EXPECT_TRUE(a + b == c);
}

TEST(Operators, Plus2) {
  S21Matrix a(2, 2);
  S21Matrix b(8, 8);
  EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(Operators, Minus1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -2.4;
  b(0, 1) = 0;
  b(1, 0) = 14.2;
  b(1, 1) = 100;
  c(0, 0) = 4.8;
  c(0, 1) = 5;
  c(1, 0) = -15.2;
  c(1, 1) = 0;
  EXPECT_TRUE(a - b == c);
}

TEST(Operators, Minus2) {
  S21Matrix a(2, 2);
  S21Matrix b(8, 8);
  EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(Operators, MulNum) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2.5;
  a(1, 0) = 5;
  a(1, 1) = -1;
  b(0, 0) = 4;
  b(0, 1) = 10;
  b(1, 0) = 20;
  b(1, 1) = -4;
  EXPECT_TRUE(a * 4 == b);
}
TEST(Operators, MulM1) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 1);
  S21Matrix c(2, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  b(0, 0) = -1;
  b(1, 0) = 2.3;
  b(2, 0) = 0;
  c(0, 0) = 3.6;
  c(1, 0) = 7.5;
  EXPECT_TRUE(a * b == c);
}

TEST(Operators, MulM2) {
  S21Matrix a(2, 3);
  S21Matrix b(5, 15);
  EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(Operators, Equal1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = 2.4;
  b(0, 1) = 5.0;
  b(1, 0) = -1;
  b(1, 1) = 100;
  EXPECT_TRUE(a == b);
}

TEST(Operators, Equal2) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -1;
  b(0, 1) = -2;
  b = a;
  EXPECT_TRUE(a == b);
}

TEST(Operators, Equal3) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -1;
  b(0, 1) = -2;
  EXPECT_FALSE(a == b);
}

TEST(Operators, EqualPlus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -2.4;
  b(0, 1) = 0;
  b(1, 0) = 14.2;
  b(1, 1) = 100;
  c(0, 0) = 0;
  c(0, 1) = 5;
  c(1, 0) = 13.2;
  c(1, 1) = 200;
  a += b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(Operators, EqualMinus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(0, 0) = 2.4;
  a(0, 1) = 5.0;
  a(1, 0) = -1;
  a(1, 1) = 100;
  b(0, 0) = -2.4;
  b(0, 1) = 0;
  b(1, 0) = 14.2;
  b(1, 1) = 100;
  c(0, 0) = 4.8;
  c(0, 1) = 5;
  c(1, 0) = -15.2;
  c(1, 1) = 0;
  a -= b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(Operators, EqualMulNum) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2.5;
  a(1, 0) = 5;
  a(1, 1) = -1;
  b(0, 0) = 4;
  b(0, 1) = 10;
  b(1, 0) = 20;
  b(1, 1) = -4;
  a *= 4;
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(Operators, EqualMulM) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 1);
  S21Matrix c(2, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  b(0, 0) = -1;
  b(1, 0) = 2.3;
  b(2, 0) = 0;
  c(0, 0) = 3.6;
  c(1, 0) = 7.5;
  a *= b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(Operators, Index1) {
  S21Matrix a(2, 2);
  EXPECT_THROW(a(4, 0), std::out_of_range);
}

TEST(Operators, IndexConst1) {
  const S21Matrix a(2, 2);
  EXPECT_TRUE(a(0, 0) == 0);
}

TEST(Operators, IndexConst2) {
  const S21Matrix a(2, 2);
  EXPECT_THROW(a(4, 0), std::out_of_range);
}

TEST(Operations, Assignment1) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  b(0, 0) = 4;
  a = std::move(b);
  EXPECT_EQ(a(0, 0), 4);
}

TEST(Operations, NoEqual) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2.5;
  a(1, 0) = 3;
  a(1, 1) = 4;
  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = -4;
  EXPECT_FALSE(a == b);
}
TEST(Operations, transpose) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;
  b(0, 0) = 1;
  b(0, 1) = 3;
  b(0, 2) = 5;
  b(1, 0) = 2;
  b(1, 1) = 4;
  b(1, 2) = 6;
  S21Matrix result = a.Transpose();
  EXPECT_TRUE(result.EqMatrix(b));
}

TEST(Operations, Determinant1) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 5;
  a(1, 0) = 5;
  a(1, 1) = 4;
  a(1, 2) = 6;
  a(2, 0) = 5.5;
  a(2, 1) = 6;
  a(2, 2) = 100;
  EXPECT_EQ(a.Determinant(), -530);
}

TEST(Operations, Determinant2) {
  S21Matrix a(1, 1);
  a(0, 0) = 5;
  EXPECT_EQ(a.Determinant(), 5);
}

TEST(Operations, Determinant3) {
  S21Matrix a(3, 5);
  EXPECT_THROW(a.Determinant(), std::invalid_argument);
}

TEST(Operations, CalcComp1) {
  S21Matrix a(3, 5);
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
}

TEST(Operations, CalcComp2) {
  S21Matrix a(1, 1);
  S21Matrix result(1, 1);
  result(0, 0) = 1;
  EXPECT_TRUE(result.EqMatrix(a.CalcComplements()));
}

TEST(Operations, CalcComp3) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;
  b(0, 0) = 0;
  b(0, 1) = 10;
  b(0, 2) = -20;
  b(1, 0) = 4;
  b(1, 1) = -14;
  b(1, 2) = 8;
  b(2, 0) = -8;
  b(2, 1) = -2;
  b(2, 2) = 4;
  EXPECT_TRUE(b.EqMatrix(a.CalcComplements()));
}

TEST(Operations, Inverse) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;
  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = -38;
  b(1, 1) = 41;
  b(1, 2) = -34;
  b(2, 0) = 27;
  b(2, 1) = -29;
  b(2, 2) = 24;
  EXPECT_TRUE(b.EqMatrix(a.InverseMatrix()));
}

TEST(Operations, Inverse2) {
  S21Matrix a(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 0;
  a(2, 1) = 0;
  a(1, 2) = 0;
  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
}

TEST(Operations, Inverse3) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix result(1, 1);
  a(0, 0) = 2;
  b(0, 0) = 0.5;
  result = a.InverseMatrix();
  EXPECT_TRUE(result(0, 0) == b(0, 0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}