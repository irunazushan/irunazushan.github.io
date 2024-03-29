#ifndef S21_ARRAY_TPP_
#define S21_ARRAY_TPP_

#include "s21_vector.h"

namespace s21 {
template <typename T, typename A>
Vector<T, A>::Vector(size_type size, const T& value, const A& allocator)
    : allocator_(allocator) {
  data_ = allocate_memory(size, size, value, allocator_);
  size_ = capacity_ = size;
}

template <typename T, typename A>
Vector<T, A>::Vector(Vector&& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      data_(other.data_),
      allocator_(std::move(other.allocator_)) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<value_type> const& items, const A& a)
    : size_(items.size()), capacity_(size_), allocator_(a) {
  data_ = allocate_memory(size_, size_, *items.begin(), allocator_);
  size_type i = 0;
  iterator p;
  try {
    iterator end = data_ + size_;
    for (p = data_; p != end; ++p) {
      traits::construct(allocator_, p, *(items.begin() + i++));
    }
  } catch (...) {
    for (iterator q = data_; q != p; ++q) {
      traits::destroy(allocator_, q);
    }
    deallocate_memory(0, capacity_, data_, allocator_);
    throw;
  }
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector& other) {
  data_ =
      allocate_memory(other.size_, other.capacity_, other.data_, allocator_);
  size_ = other.size_;
  capacity_ = other.capacity_;
}

template <typename T, typename A>
Vector<T, A>::~Vector() {
  deallocate_memory(size_, capacity_, data_, allocator_);
  size_ = capacity_ = 0;
}

template <typename T, typename A>
Vector<T, A>& Vector<T, A>::operator=(const Vector& other) {
  if (this != &other) {
    Vector tmp(other);
    swap(tmp);
  }
  return *this;
}

template <typename T, typename A>
Vector<T, A>& Vector<T, A>::operator=(Vector&& other) {
  if (this != &other) {
    deallocate_memory(size_, capacity_, data_, allocator_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    allocator_ = std::move(other.allocator_);
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

template <typename T, typename A>
T& Vector<T, A>::at(size_type pos) {
  if (!(pos < size())) {
    throw std::out_of_range("Index is out of range of vector");
  }
  return data_[pos];
}

template <typename T, typename A>
const T& Vector<T, A>::at(size_type pos) const {
  if (!(pos < size())) {
    throw std::out_of_range("Index is out of range of vector");
  }
  return data_[pos];
}

template <typename T, typename A>
void Vector<T, A>::reserve(size_type new_cap) {
  if (new_cap > capacity_ && new_cap >= size_) {
    Vector<T, A> tmp;
    tmp.data_ = allocate_memory(size_, new_cap, data_, allocator_);
    tmp.size_ = size_;
    tmp.capacity_ = new_cap;
    swap(tmp);
  }
}

template <typename T, typename A>
void Vector<T, A>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  Vector<T, A> tmp;
  tmp.data_ = allocate_memory(size_, size_, data_, allocator_);
  tmp.size_ = size_;
  tmp.capacity_ = size_;
  swap(tmp);
}

template <typename T, typename A>
void Vector<T, A>::clear() noexcept {
  for (iterator p = data_; p != data_ + size_; ++p) {
    traits::destroy(allocator_, p);
  }
  size_ = 0;
}

template <typename T, typename A>
void Vector<T, A>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ * 2 + 1);
  }
  traits::construct(allocator_, data_ + size_, value);
  size_++;
}

template <typename T, typename A>
void Vector<T, A>::push_back(value_type&& value) {
  if (size_ == capacity_) {
    reserve(capacity_ * 2 + 1);
  }
  traits::construct(allocator_, data_ + size_, std::move(value));
  size_++;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::insert(iterator pos,
                                                     const_reference value) {
  size_type offset = pos - begin();
  if (size_ == capacity_) {
    reserve(capacity_ * 2 + 1);
    pos = begin() + offset;
  }
  size_++;
  std::copy_backward(begin() + offset, end() - 1, end());
  *(begin() + offset) = value;
  return begin() + offset;
}

template <typename T, typename A>
void Vector<T, A>::erase(iterator pos) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("pos is out of range");
    return;
  }
  if (pos != end() - 1) {
    std::move(pos + 1, end(), pos);
  }
  traits::destroy(allocator_, end() - 1);
  size_--;
}

template <typename T, typename A>
void Vector<T, A>::pop_back() {
  traits::destroy(allocator_, end() - 1u);
  size_--;
}

template <typename T, typename A>
void Vector<T, A>::swap(Vector& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
  std::swap(allocator_, other.allocator_);
}

template <typename T, typename A>
void Vector<T, A>::resize(size_type count) {
  if (count > capacity_) reserve(count);
  if (size_ > count) {
    while (size_ != count) pop_back();
  }
  while (size_ < count) {
    traits::construct(allocator_, data_ + size_);
    size_++;
  }
}

template <typename T, typename A>
void Vector<T, A>::resize(size_type count, const_reference value) {
  if (count > capacity_) reserve(count);
  if (size_ > count) {
    while (size_ != count) pop_back();
  }
  while (size_ < count) {
    traits::construct(allocator_, data_ + size_, value);
    size_++;
  }
}

template <typename T, typename A>
T* Vector<T, A>::allocate_memory(size_type size, size_type capacity,
                                 const T& value, A& allocator) {
  value_type* new_arr = traits::allocate(allocator, capacity);
  iterator p;
  try {
    iterator end = new_arr + size;
    for (p = new_arr; p != end; ++p) {
      traits::construct(allocator, p, value);
    }
  } catch (...) {
    for (iterator q = new_arr; q != p; ++q) {
      traits::destroy(allocator, q);
    }
    traits::deallocate(allocator, new_arr, capacity);
    throw;
  }
  return new_arr;
}

template <typename T, typename A>
T* Vector<T, A>::allocate_memory(size_type size, size_type capacity,
                                 const_pointer arr, A& allocator) {
  value_type* new_arr = traits::allocate(allocator, capacity);
  iterator p;
  try {
    size_type i = 0;
    iterator end = new_arr + size;
    for (p = new_arr; p != end; ++p) {
      traits::construct(allocator, p, arr[i++]);
    }
  } catch (...) {
    for (iterator q = new_arr; q != p; ++q) {
      traits::destroy(allocator, q);
    }
    traits::deallocate(allocator, new_arr, capacity);
    throw;
  }
  return new_arr;
}

template <typename T, typename Alloc>
template <class... Args>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::emplace(
    const_iterator pos, Args&&... args) {
  if (pos == cend()) {
    return emplace_back(std::forward<Args>(args)...);
  }
  if (capacity_ == 0) {
    capacity_ = 1;
  } else {
    reserve(capacity_ * 2);
  }
  Vector<T, Alloc>::iterator it_res;
  Vector<T, Alloc>::const_iterator it = cbegin();
  for (; it != pos; ++it) {
  }
  it_res = insert(it, T(std::forward<Args>(args)...));
  return it_res;
}

template <typename T, typename Alloc>
template <class... Args>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::emplace_back(
    Args&&... args) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      capacity_ = 1;
    } else {
      reserve(capacity_ * 2);
    }
  }

  auto res = traits::allocate(allocator_, 1);
  traits::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
  return data_[size_++];
}

template <typename T, typename A>
void Vector<T, A>::deallocate_memory(size_type size, size_type capacity,
                                     pointer arr, A& allocator) {
  if (arr != nullptr) {
    for (iterator p = arr; p != arr + size; ++p) {
      traits::destroy(allocator, p);
    }
    traits::deallocate(allocator, arr, capacity);
  }
}

template <typename T, typename A>
template <class... Args>
typename Vector<T, A>::iterator Vector<T, A>::insert_many(const_iterator pos,
                                                          Args&&... args) {
  std::initializer_list<value_type> items{std::forward<Args>(args)...};
  auto it = begin() + (pos - cbegin());
  for (const auto& item : items) {
    it = insert(it, item);
    ++it;
  }
  return it;
}

template <typename T, typename A>
template <class... Args>
void Vector<T, A>::insert_many_back(Args&&... args) {
  std::initializer_list<value_type> items{std::forward<Args>(args)...};
  for (auto& item : items) {
    push_back(item);
  }
}

}  // namespace s21

#endif
