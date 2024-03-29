#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <class T, size_t N>
class Array {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

 private:
  size_type size_;
  value_type array_[N];

 public:
  Array() : size_(N){};
  Array(std::initializer_list<value_type> const& items);
  Array(const Array& other);
  Array(Array&& other) noexcept;
  ~Array() = default;

  Array& operator=(const Array& other);
  Array& operator=(Array&& other) noexcept;
  reference at(size_type pos);
  reference operator[](size_type pos) { return array_[pos]; };
  const_reference front() const { return array_[0]; }
  const_reference back() const { return array_[size_ - 1]; }
  iterator data() { return array_; }

  iterator begin() { return array_; }
  iterator end() { return array_ + size_; }
  const_iterator cbegin() const { return array_; }
  const_iterator cend() const { return array_ + size_; }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return size_; }

  void swap(Array& other);
  void fill(const_reference value);
};
}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_ARRAY_H
