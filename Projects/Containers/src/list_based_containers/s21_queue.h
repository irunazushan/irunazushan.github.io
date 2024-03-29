#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() = default;
  queue(std::initializer_list<value_type> const &items) : lst(items) {}
  queue(const queue &q) : lst(q.lst) {}
  queue(queue &&q) : lst(std::move(q.lst)) {}
  ~queue() = default;
  queue &operator=(const queue &q) {
    for (auto it = q.lst.cbegin(); it != q.lst.cend(); ++it) {
      this->push_back(*it);
    }
    return *this;
  }
  queue &operator=(queue &&q) {
    lst.swap(q.lst);
    return *this;
  }

  const_reference front() { return lst.front(); }
  const_reference back() { return lst.back(); }
  bool empty() { return lst.empty(); }
  size_type size() { return lst.size(); }
  void push(const_reference value) { lst.push_back(value); }
  void pop() { lst.pop_front(); }
  void swap(queue &other) { lst.swap(other.lst); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    lst.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> lst;
};
}  // namespace s21

#endif
