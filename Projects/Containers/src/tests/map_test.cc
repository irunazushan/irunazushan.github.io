#include <gtest/gtest.h>

#include <map>

#include "test_runner.h"

TEST(Constructor, test1) {
  s21::map<int, std::string> s21Map;
  std::map<int, std::string> origMap;
  EXPECT_EQ(s21Map.empty(), origMap.empty());
}

TEST(Constructor, test2) {
  s21::map<int, std::string> s21Map = {
      {2, "Tea"}, {4, "Coffee"}, {-7, "Breakfast"}, {9, "Lunch"}};
  std::map<int, std::string> origMap = {
      {2, "Tea"}, {4, "Coffee"}, {-7, "Breakfast"}, {9, "Lunch"}};
  EXPECT_EQ(s21Map.size(), origMap.size());
  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(Constructor, test3) {
  s21::map<int, std::string> s21Map = {};
  std::map<int, std::string> origMap = {};
  EXPECT_EQ(s21Map.size(), origMap.size());
  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(Constructor, test4) {
  s21::map<char, int> s21Map = {{'a', 2}, {'c', 4}, {'b', 6}};
  std::map<char, int> origMap = {{'a', 2}, {'c', 4}, {'b', 6}};
  s21::map<char, int> s21Map_copy = s21Map;
  std::map<char, int> origMap_copy = origMap;
  EXPECT_EQ(s21Map_copy.size(), origMap_copy.size());
  auto my_it = s21Map_copy.begin();
  auto orig_it = origMap_copy.begin();
  for (; my_it != s21Map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(Constructor, test5) {
  s21::map<int, int> s21Map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> origMap = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21Map_copy = std::move(s21Map);
  std::map<int, int> origMap_copy = std::move(origMap);
  EXPECT_EQ(s21Map.size(), origMap.size());
  EXPECT_EQ(s21Map_copy.size(), origMap_copy.size());
  auto my_it = s21Map_copy.begin();
  auto orig_it = origMap_copy.begin();
  ++my_it;
  ++orig_it;
  for (; my_it != s21Map_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(Operator, test1) {
  s21::map<int, std::string> s21Map = {{2, "Tea"}, {1, "Coffe"}, {7, "Juice"}};
  std::map<int, std::string> origMap = {{2, "Tea"}, {1, "Coffe"}, {7, "Juice"}};
  origMap[7] = "Coffe";
  s21Map[1] = "Juice";
  origMap[1] = "Juice";
  EXPECT_TRUE(s21Map[1] == origMap[1]);
  EXPECT_TRUE(s21Map[2] == origMap[2]);
  EXPECT_FALSE(s21Map[7] == origMap[7]);
}

TEST(Operator, test2) {
  s21::map<char, std::string> s21Map = {{2, "Tea"}, {1, "Coffe"}, {7, "Juice"}};
  EXPECT_THROW(s21Map.at('8') = "Pancake", std::out_of_range);
}

TEST(Operator, test3) {
  s21::map<int, std::string> s21Map = {{2, "Tea"}, {1, "Coffe"}, {7, "Juice"}};
  std::map<int, std::string> origMap = {{2, "Tea"}, {1, "Coffe"}, {7, "Juice"}};
  origMap.at(7) = "Coffe";
  s21Map.at(1) = "Juice";
  origMap.at(1) = "Juice";
  EXPECT_TRUE(s21Map[1] == origMap[1]);
  EXPECT_TRUE(s21Map[2] == origMap[2]);
  EXPECT_FALSE(s21Map[7] == origMap[7]);
}

TEST(Methods, test1) {
  s21::map<char, std::string> s21Map;
  std::map<char, std::string> origMap;
  EXPECT_TRUE(s21Map.empty() == origMap.empty());
  s21Map.insert(std::make_pair('L', "Banana"));
  EXPECT_FALSE(s21Map.empty() == origMap.empty());
  EXPECT_EQ(s21Map.size(), 1);
}

TEST(Methods, test2) {
  s21::map<int, int> s21Map;
  std::map<int, int> origMap;
  s21Map.clear();
  origMap.clear();
  EXPECT_EQ(s21Map.empty(), origMap.empty());
  s21Map.insert(std::make_pair(45, 1));
  origMap.insert(std::make_pair(45, 1));
  EXPECT_EQ(s21Map.empty(), origMap.empty());
  s21Map.clear();
  origMap.clear();
  EXPECT_EQ(s21Map.empty(), origMap.empty());
}

TEST(Methods, test3) {
  s21::map<int, char> s21Map;
  std::map<int, char> origMap;
  s21Map.insert(std::make_pair(4, 'a'));
  s21Map.insert(std::make_pair(-2, 'a'));
  s21Map.insert(std::make_pair(9, 'a'));
  origMap.insert(std::make_pair(4, 'a'));
  origMap.insert(std::make_pair(-2, 'a'));
  origMap.insert(std::make_pair(9, 'a'));

  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = s21Map.insert(std::make_pair(4, 'a'));
  auto pr2 = origMap.insert(std::make_pair(4, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(Methods, test4) {
  s21::map<int, char> s21Map;
  std::map<int, char> origMap;
  s21Map.insert(std::make_pair(4, 'a'));
  s21Map.insert(std::make_pair(-2, 'a'));
  s21Map.insert(std::make_pair(9, 'a'));
  origMap.insert(std::make_pair(4, 'a'));
  origMap.insert(std::make_pair(-2, 'a'));
  origMap.insert(std::make_pair(9, 'a'));

  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = s21Map.insert(std::make_pair(4, 'a'));
  auto pr2 = origMap.insert(std::make_pair(4, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(Methods, test5) {
  s21::map<int, std::string> s21Map;
  std::map<int, std::string> origMap;
  s21Map.insert(1, "apple");
  s21Map.insert(2, "abba");
  s21Map.insert(3, "banana");
  origMap.insert(std::make_pair(1, "apple"));
  origMap.insert(std::make_pair(2, "abba"));
  origMap.insert(std::make_pair(3, "banana"));

  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = s21Map.insert_or_assign(1, "noApple");
  auto i = origMap.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(Methods, test6) {
  s21::map<int, std::string> s21Map = {
      {2, "Tea"}, {4, "Coffee"}, {-7, "Breakfast"}, {9, "Lunch"}};
  std::map<int, std::string> origMap = {
      {2, "Tea"}, {4, "Coffee"}, {-7, "Breakfast"}, {9, "Lunch"}};
  EXPECT_EQ(s21Map.size(), origMap.size());
  s21Map.erase(s21Map.begin());
  origMap.erase(origMap.begin());
  EXPECT_EQ(s21Map.size(), origMap.size());
  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(Methods, test7) {
  s21::map<int, int> s21Map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  s21Map.swap(my_swap_map);
  EXPECT_EQ(s21Map.size(), 2);
  EXPECT_EQ(my_swap_map.size(), 1);
  auto x = (*(s21Map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(Methods, test8) {
  s21::map<int, int> s21Map = {{10, 200}, {14, 4}, {32, 2}};
  s21::map<int, int> s21Map_merge = {{30, 3}, {4, 79}};

  std::map<int, int> origMap = {{10, 200}, {14, 4}, {32, 2}};
  std::map<int, int> origMap_merge = {{30, 3}, {4, 79}};

  s21Map.merge(s21Map_merge);
  origMap.merge(origMap_merge);

  auto my_it = s21Map.begin();
  auto orig_it = origMap.begin();
  for (; my_it != s21Map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
  }
}

TEST(Methods, test9) {
  s21::map<int, int> l{std::make_pair(5, 5), std::make_pair(8, 8)};
  l.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                std::make_pair(3, 3));
  EXPECT_EQ(l.size(), 5);
}
