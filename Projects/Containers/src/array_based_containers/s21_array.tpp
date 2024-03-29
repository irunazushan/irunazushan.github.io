#include "s21_array.h"

namespace s21 {
template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const& items) : size_(N) {
  if (size_ < items.size()) throw std::out_of_range("Too many initializers");
  size_t i = 0;
  for (const auto& item : items) {
    array_[i++] = item;
  }
}

template <class T, size_t N>
Array<T, N>::Array(const Array& other) : size_(other.size_) {
  std::copy(other.cbegin(), other.cend(), array_);
}

template <class T, size_t N>
Array<T, N>::Array(Array&& other) noexcept : size_(other.size_) {
  std::move(other.array_, other.array_ + other.size_, array_);
  other.size_ = 0;
}

template <class T, size_t N>
Array<T, N>& Array<T, N>::operator=(const Array& other) {
  if (this != &other) {
    size_ = other.size_;
    std::copy(other.cbegin(), other.cend(), array_);
  }
  return *this;
}

template <class T, size_t N>
Array<T, N>& Array<T, N>::operator=(Array&& other) noexcept {
  if (this != &other) {
    size_ = other.size_;
    std::move(other.array_, other.array_ + other.size_, array_);
    other.size_ = 0;
  }
  return *this;
}

template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index is out of range");
  return array_[pos];
}

template <class T, size_t N>
void Array<T, N>::swap(Array& other) {
  std::swap_ranges(array_, array_ + size_, other.array_);
  std::swap(size_, other.size_);
}

template <class T, size_t N>
void Array<T, N>::fill(const_reference value) {
  std::fill(array_, array_ + size_, value);
}
};  // namespace s21
