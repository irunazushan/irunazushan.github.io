#ifndef __S21_MAP_H__
#define __S21_MAP_H__

#include <vector>

#include "s21_avl_tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public AVLTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;

  map();
  map(const map& other);
  map(map&& other);
  map(std::initializer_list<value_type> const& items);
  ~map();

  map& operator=(const map& other);
  map& operator=(map&& other);
  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  class iterator : public AVLTree<key_type, mapped_type>::Iterator {
   public:
    iterator();
    iterator(typename AVLTree<key_type, mapped_type>::Node* node,
             typename AVLTree<key_type, mapped_type>::Node* lastNode = nullptr);
    value_type operator*();
  };

  iterator begin();
  iterator end();
  iterator find(const Key& key);
  std::pair<iterator, bool> insert(value_type pair);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  value_type pair;
};

}  // namespace s21

#include "s21_map.tpp"

#endif
