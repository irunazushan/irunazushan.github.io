#include "s21_list.h"
namespace s21 {
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), root(nullptr), m_size(0) {
  root = new node(T{});
  root->next = root;
  root->prev = root;
}

template <typename T>
list<T>::list(size_t n) : list() {
  while (m_size < n) {
    push_back(T{});
  }
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) {
  this->swap(other);
  return (*this);
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  for (auto it = other.cbegin(); it != other.cend(); ++it) {
    this->push_back(*it);
  }
  return (*this);
}

template <typename T>
list<T>::list(std::initializer_list<T> const& items) : list() {
  for (const auto& val : items) {
    push_back(val);
  }
}

template <typename T>
list<T>::list(list<T>&& other) : list() {
  this->swap(other);
}

template <typename T>
list<T>::list(const list<T>& other) : list() {
  for (auto it = other.cbegin(); it != other.cend(); ++it) {
    this->push_back(*it);
  }
}

template <typename T>
list<T>::~list() noexcept {
  clear();
  delete root;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& value) {
  node* new_node = new node(value);
  new_node->prev = pos.cur_->prev;
  new_node->next = pos.cur_;
  new_node->prev->next = new_node;
  new_node->next->prev = new_node;
  head = root->next;
  tail = root->prev;

  ++m_size;
  return iterator(new_node);
}

template <class T>
void list<T>::push_back(const T& value) {
  insert(end(), value);
}

template <typename T>
const T& list<T>::front() const {
  return head->value_;
}

template <class T>
const T& list<T>::back() const {
  return tail->value_;
}

template <typename T>
void list<T>::erase(iterator pos) {
  pos.cur_->prev->next = pos.cur_->next;
  pos.cur_->next->prev = pos.cur_->prev;
  head = root->next;
  tail = root->prev;
  delete pos.cur_;
  --m_size;
}

template <typename T>
void list<T>::clear() {
  while (m_size != 0) {
    pop_back();
  }
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(this->root, other.root);
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->m_size, other.m_size);
}
template <typename T>
void list<T>::push_front(const T& value) {
  insert(begin(), value);
}

template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

template <typename T>
void list<T>::merge(list& other) {
  if (empty()) {
    swap(other);
  } else {
    auto it_this = this->begin();
    auto it_other = other.begin();
    while (it_other != other.end()) {
      if (it_this != this->end() && *it_other >= *it_this) {
        ++it_this;
      } else {
        insert(it_this, *it_other);
        ++it_other;
      }
    }
  }
  other.clear();
}

template <typename T>
void list<T>::sort() {
  if (!empty()) {
    for (auto it1 = begin(); it1 != end(); ++it1) {
      for (auto it2 = begin(); it2 != end(); ++it2) {
        if (*it1 < *it2) {
          std::swap(*it1, *it2);
        }
      }
    }
  }
}

template <class T>
void list<T>::reverse() {
  if (!empty()) {
    std::swap(head, tail);
    for (auto it = begin(); it != end(); ++it) {
      std::swap(it.cur_->prev, it.cur_->next);
    }
  }
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    pos.cur_->prev->next = other.head;
    other.head->prev = pos.cur_->prev;
    pos.cur_->prev = other.tail;
    other.tail->next = pos.cur_;

    m_size += other.m_size;
    other.m_size = 0;
  }
}

template <class T>
void list<T>::unique() {
  if (!empty()) {
    for (auto it = begin(); it != end(); ++it) {
      node* prev = it.cur_->prev;
      if (prev != nullptr && it.cur_->value_ == prev->value_) {
        erase(prev);
      }
    }
  }
}

}  // namespace s21