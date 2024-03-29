#include <gtest/gtest.h>

#include <queue>

#include "test_runner.h"

TEST(Queue, Default) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(Queue, Initializer_list) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(Queue, Copy_constructor) {
  s21::queue<int> s21_queue{1, 2, 3};
  s21::queue<int> std_queue(s21_queue);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(Queue, Move_constructor) {
  s21::queue<int> s21_queue{1, 2, 3};
  s21::queue<int> s21_queue_move{1, 2, 3};
  s21::queue<int> std_queue = std::move(s21_queue_move);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(Queue, Front) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(Queue, Empty) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(Queue, Push) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  s21_queue.push(5);
  std_queue.push(5);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(Queue, Pop) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(Queue, Swap) {
  s21::queue<int> s21{1, 2, 3};
  s21::queue<int> s22{4, 5, 6};
  EXPECT_EQ(s21.front(), 1);
  EXPECT_EQ(s22.front(), 4);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.front(), 2);
  EXPECT_EQ(s22.front(), 5);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.front(), 3);
  EXPECT_EQ(s22.front(), 6);
  s21.pop();
  s22.pop();

  s21.push(1);
  s21.push(2);
  s21.push(3);

  s22.push(4);
  s22.push(5);
  s22.push(6);

  s21.swap(s22);

  EXPECT_EQ(s21.front(), 4);
  EXPECT_EQ(s22.front(), 1);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.front(), 5);
  EXPECT_EQ(s22.front(), 2);
  s21.pop();
  s22.pop();
  EXPECT_EQ(s21.front(), 6);
  EXPECT_EQ(s22.front(), 3);
}

TEST(Queue, Insert_many_back) {
  s21::queue<int> queue = {1, 2, 3};
  queue.insert_many_back(65, 67, 87, 45, 67, 27, 9);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(65);
  std_queue.push(67);
  std_queue.push(87);
  std_queue.push(45);
  std_queue.push(67);
  std_queue.push(27);
  std_queue.push(9);

  int i = 0;
  while (i < 10) {
    EXPECT_EQ(queue.front(), std_queue.front());
    queue.pop();
    std_queue.pop();
    i++;
  }
}
