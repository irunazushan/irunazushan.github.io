#include <gtest/gtest.h>

#include <set>

#include "test_runner.h"

TEST(Multiset, Constructors_default) {
  s21::multiset<int> s21_set;
  std::multiset<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset, initializer_list) {
  s21::multiset<int> s21_set{1, 2, 3, 4, 5};
  std::multiset<int> std_set{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset, initializer_list_same) {
  s21::multiset<int> s21_set{1, 2, 3, 3, 5};
  std::multiset<int> std_set{1, 2, 3, 3, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset, rule5_copy_con) {
  s21::multiset<int> s21_set{1, 2, 3, 3, 5};
  std::multiset<int> std_set{1, 2, 3, 3, 5};

  s21::multiset<int> s21_cop = s21::multiset(s21_set);
  std::multiset<int> std_cop = std::multiset(std_set);

  EXPECT_NE(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Multiset, rule5_move_con) {
  s21::multiset<int> s21_set{1, 2, 3, 3, 5};
  std::multiset<int> std_set{1, 2, 3, 3, 5};

  s21::multiset<int> s21_cop = s21::multiset(std::move(s21_set));
  std::multiset<int> std_cop = std::multiset(std::move(std_set));

  EXPECT_EQ(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Multiset, rule5_copy_ass) {
  s21::multiset<int> s21_set{1, 2, 3, 3, 5};
  std::multiset<int> std_set{1, 2, 3, 3, 5};

  auto s21_cop = s21_set;
  auto std_cop = std_set;

  EXPECT_NE(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Multiset, rule5_move_ass) {
  s21::multiset<int> s21_set{1, 2, 3, 3, 5};
  std::multiset<int> std_set{1, 2, 3, 3, 5};

  auto s21_cop = std::move(s21_set);
  auto std_cop = std::move(std_set);

  EXPECT_EQ(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Multiset, Insert_many) {
  s21::multiset<int> mult{6, 7, 8, 8, 9};
  auto res = mult.insert_many(1, 2, 3);
  EXPECT_EQ(mult.size(), 8);
}
