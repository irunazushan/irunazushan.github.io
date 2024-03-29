#ifndef LIST_H

#define LIST_H

namespace s21 {

template <typename T>
class list {
 private:
  struct node {
    T value_;
    node* prev;
    node* next;
    node(const T& value) : value_(value), prev(nullptr), next(nullptr) {}
  };

  node* head;
  node* tail;
  node* root;
  size_t m_size;

 public:
  template <typename D>
  class ListIterator {
   public:
    using iterator = ListIterator<D>;
    node* cur_;
    ListIterator() : cur_(nullptr) {}
    ListIterator(node* cur) : cur_(cur) {}
    T& operator*() { return cur_->value_; }
    iterator& operator++() {
      cur_ = cur_->next;
      return *this;
    }
    iterator& operator--() {
      cur_ = cur_->prev;
      return *this;
    }
    bool operator!=(const iterator& other) const { return cur_ != other.cur_; }
    bool operator==(const iterator& other) const { return cur_ == other.cur_; }
  };

  template <typename D>
  class ListConstIterator : public ListIterator<D> {
   public:
    ListConstIterator() : ListIterator<D>() {}
    ListConstIterator(node* cur_) : ListIterator<D>(cur_) {}
    const T& operator*() const { return this->cur_->value_; }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  list();
  list(size_t n);
  list(std::initializer_list<T> const& items);
  list(list&& other);
  list(const list& other);
  ~list() noexcept;
  list& operator=(list&& other);
  list& operator=(const list& other);
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(root); }
  const_iterator cbegin() const { return const_iterator(head); }
  const_iterator cend() const { return const_iterator(root); }
  const T& front() const;
  const T& back() const;
  iterator insert(iterator pos, const T& value);
  void push_back(const T& value);
  void erase(iterator pos);
  void pop_back() { erase(tail); }
  void clear();
  size_t max_size() { return PTRDIFF_MAX / sizeof(node); }
  size_t size() { return m_size; }
  bool empty() { return m_size == 0; }
  void swap(list& other);
  void push_front(const T& value);
  void pop_front();
  void merge(list& other);
  void sort();
  void reverse();
  void splice(const_iterator pos, list& other);
  void unique();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator result = pos;
    (void(result = insert(result, std::forward<Args>(args))), ...);
    return result;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (void(push_back(std::forward<Args>(args))), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (void(push_front(std::forward<Args>(args))), ...);
  }
};

}  // namespace s21

#include "s21_list.tpp"
#endif