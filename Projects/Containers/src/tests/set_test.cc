#include <gtest/gtest.h>

#include <set>

#include "test_runner.h"

TEST(Set, Constructors_default) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, initializer_list) {
  s21::set<int> s21_set{1, 2, 3, 4, 5};
  std::set<int> std_set{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, initializer_list_same) {
  s21::set<int> s21_set{1, 2, 3, 3, 5};
  std::set<int> std_set{1, 2, 3, 3, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, rule5_copy_con) {
  s21::set<int> s21_set{1, 2, 3, 3, 5};
  std::set<int> std_set{1, 2, 3, 3, 5};

  s21::set<int> s21_cop = s21::set(s21_set);
  std::set<int> std_cop = std::set(std_set);

  EXPECT_NE(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Set, rule5_move_con) {
  s21::set<int> s21_set{1, 2, 3, 3, 5};
  std::set<int> std_set{1, 2, 3, 3, 5};

  s21::set<int> s21_cop = s21::set(std::move(s21_set));
  std::set<int> std_cop = std::set(std::move(std_set));

  EXPECT_EQ(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Set, rule5_copy_ass) {
  s21::set<int> s21_set{1, 2, 3, 3, 5};
  std::set<int> std_set{1, 2, 3, 3, 5};

  auto s21_cop = s21_set;
  auto std_cop = std_set;

  EXPECT_NE(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Set, rule5_move_ass) {
  s21::set<int> s21_set{1, 2, 3, 3, 5};
  std::set<int> std_set{1, 2, 3, 3, 5};

  auto s21_cop = std::move(s21_set);
  auto std_cop = std::move(std_set);

  EXPECT_EQ(s21_set.size(), 0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_cop.size(), std_cop.size());
  EXPECT_EQ(s21_cop.empty(), std_cop.empty());
}

TEST(Set, Insert_many) {
  s21::set<int> s21_set{6, 7, 8, 8, 9};
  auto res = s21_set.insert_many(1, 2, 3);
  EXPECT_EQ(s21_set.size(), 7);
}
