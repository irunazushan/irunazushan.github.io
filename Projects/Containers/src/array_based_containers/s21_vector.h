#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, class Allocator = std::allocator<T>>
class Vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  using pointer = T*;
  using const_pointer = const T*;
  using allocator_type = Allocator;
  using traits = std::allocator_traits<Allocator>;

  Vector()
      : size_(0u), capacity_(0u), data_(nullptr), allocator_(Allocator()) {}
  Vector(std::initializer_list<value_type> const& items,
         const Allocator& allocator = Allocator());
  Vector(const Allocator& allocator)
      : size_(0u), capacity_(0u), data_(nullptr), allocator_(allocator) {}
  Vector(size_type size, const T& value = T(),
         const Allocator& allocator = Allocator());
  Vector(const Vector& other);
  Vector(Vector&& other);
  ~Vector();

  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos) { return at(pos); }
  const_reference operator[](size_type pos) const { return at(pos); }
  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }
  reference back() { return size() == 0 ? data_[0] : data_[size_ - 1]; }
  const_reference back() const {
    return size() == 0 ? data_[0] : data_[size_ - 1];
  }
  pointer data() { return data_; }
  const_pointer data() const { return data_; }

  iterator begin() { return data_; }
  const_iterator cbegin() const { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator cend() const { return data_ + size_; }

  bool empty() const { return cbegin() == cend(); }
  size_type size() const { return size_; }
  size_type capacity() const { return capacity_; }
  size_type max_size() const { return traits::max_size(allocator_); }
  void reserve(size_type size);
  void shrink_to_fit();

  void clear() noexcept;
  void push_back(const_reference value);
  void push_back(value_type&& value);
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void pop_back();
  void swap(Vector& other);
  void resize(size_type count);
  void resize(size_type count, const_reference value);

  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args);

  template <class... Args>
  reference emplace_back(Args&&... args);

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  size_type size_;
  size_type capacity_;
  T* data_;
  Allocator allocator_;

  pointer allocate_memory(size_type size, size_type capacity, const T& value,
                          Allocator& allocator);
  pointer allocate_memory(size_type size, size_type capacity, const_pointer arr,
                          Allocator& allocator);
  void deallocate_memory(size_type size, size_type capacity, pointer arr,
                         Allocator& allocator);
  void swap_(Vector& to, Vector& from);
};
}  // namespace s21

#include "s21_vector.tpp"

#endif  // S21_VECTOR_H
