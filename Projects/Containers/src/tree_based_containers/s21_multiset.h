#ifndef S21_MULTISET_H
#define S21_MULTISET_H
#include <vector>

#include "s21_avl_tree.h"
namespace s21 {

template <typename Key>
class multiset : public AVLTree<Key, Key> {
 public:
  using iterator = typename AVLTree<Key, Key>::Iterator;

  multiset() : AVLTree<Key, Key>(){};
  multiset(std::initializer_list<Key> const& items) {
    for (const Key& item : items) {
      insert(item);
    }
  }
  std::pair<typename AVLTree<Key, Key>::Iterator, bool> insert(const Key& key) {
    return AVLTree<Key, Key>::insert(key, key);
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
