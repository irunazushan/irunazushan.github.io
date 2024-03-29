#ifndef S21_SET_H
#define S21_SET_H
#include <vector>

#include "s21_avl_tree.h"
namespace s21 {

template <typename Key>
class set : public AVLTree<Key, Key> {
 public:
  set() : AVLTree<Key, Key>(){};
  set(std::initializer_list<Key> const& items) {
    for (const Key& item : items) {
      insert(item);
    }
  }
  std::pair<typename AVLTree<Key, Key>::Iterator, bool> insert(const Key& key) {
    std::pair<typename AVLTree<Key, Key>::Iterator, bool> result;
    if (!AVLTree<Key, Key>::SearchNode(AVLTree<Key, Key>::root_, key)) {
      result = AVLTree<Key, Key>::insert(key, key);
    } else {
      result.first = nullptr;
      result.second = false;
    }
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<typename AVLTree<Key, Key>::Iterator, bool>>
  insert_many(Args&&... args) {
    std::vector<std::pair<typename AVLTree<Key, Key>::Iterator, bool>> result;
    (result.emplace_back(insert(std::forward<Args>(args))), ...);
    return result;
  }
};

}  // namespace s21
#endif
