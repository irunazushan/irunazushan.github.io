#ifndef S21_STACK_H
#define S21_STACK_H
#include "s21_list.h"
namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() = default;
  stack(std::initializer_list<value_type> const &items) : lst(items) {}
  stack(const stack &s) : lst(s.lst) {}
  stack(stack &&s) : lst(std::move(s.lst)) {}
  ~stack() = default;
  stack &operator=(const stack &s) {
    for (auto it = s.lst.cbegin(); it != s.lst.cend(); ++it) {
      this->push_back(*it);
    }
    return *this;
  }
  stack &operator=(stack &&s) {
    lst.swap(s.lst);
    return *this;
  }

  const_reference top() { return lst.back(); }
  bool empty() { return lst.empty(); }
  size_type size() { return lst.size(); }
  void push(const_reference value) { lst.push_back(value); }
  void pop() { lst.pop_back(); }
  void swap(stack &other) { lst.swap(other.lst); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    lst.insert_many_front(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> lst;
};
}  // namespace s21

#endif
