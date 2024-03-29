#include <gtest/gtest.h>

#include <stack>

#include "test_runner.h"

TEST(Stack, Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Initializer_list) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(Stack, Copy_constructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  s21::stack<int> std_stack(s21_stack);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Move_constructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  s21::stack<int> s21_stack_move{1, 2, 3};
  s21::stack<int> std_stack = std::move(s21_stack_move);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Top) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Empty) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Push) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  s21_stack.push(5);
  std_stack.push(5);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Pop) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Swap) {
  s21::stack<int> s21{1, 2, 3};
  s21::stack<int> s22{4, 5, 6};
  EXPECT_EQ(s21.top(), 3);
  EXPECT_EQ(s22.top(), 6);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.top(), 2);
  EXPECT_EQ(s22.top(), 5);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.top(), 1);
  EXPECT_EQ(s22.top(), 4);

  s21.push(1);
  s21.push(2);
  s21.push(3);

  s22.push(4);
  s22.push(5);
  s22.push(6);

  s21.swap(s22);

  EXPECT_EQ(s22.top(), 3);
  EXPECT_EQ(s21.top(), 6);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s22.top(), 2);
  EXPECT_EQ(s21.top(), 5);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s22.top(), 1);
  EXPECT_EQ(s21.top(), 4);
}

TEST(Stack, Insert_many_front) {
  s21::stack<int> stack = {1, 2, 3};
  stack.insert_many_front(65, 67, 87, 45, 67, 27, 9);
  s21::stack<int> result = {9, 27, 67, 45, 87, 67, 65, 1, 2, 3};
  int i = 0;
  while (i < 10) {
    EXPECT_EQ(stack.top(), result.top());
    stack.pop();
    result.pop();
    i++;
  }
}
