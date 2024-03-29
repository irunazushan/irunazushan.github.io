namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : AVLTree<Key, T>(){};

template <typename Key, typename T>
map<Key, T>::map(const map& other) : AVLTree<Key, T>(other){};

template <typename Key, typename T>
map<Key, T>::map(map&& other) : AVLTree<Key, T>(std::move(other)){};

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) {
  for (const auto& val : items) {
    insert(val);
  }
}

template <typename Key, typename T>
map<Key, T>::~map() = default;

template <typename Key, typename T>
typename map<Key, T>::map& map<Key, T>::operator=(const map& other) {
  if (this != &other) {
    AVLTree<Key, T>::operator=(other);
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::map& map<Key, T>::operator=(map&& other) {
  if (this != &other) {
    AVLTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  typename AVLTree<Key, T>::Node* result =
      AVLTree<Key, T>::SearchNode(AVLTree<Key, T>::root_, key);
  if (result == nullptr)
    throw std::out_of_range(
        "I couldn't find any key like this here in the map");
  return result->value_;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return at(key);
}

template <typename Key, typename T>
map<Key, T>::iterator::iterator() : AVLTree<Key, T>::Iterator(){};

template <typename Key, typename T>
map<Key, T>::iterator::iterator(typename AVLTree<Key, T>::Node* node,
                                typename AVLTree<Key, T>::Node* lastNode)
    : AVLTree<Key, T>::Iterator(node, lastNode) {}

template <typename Key, typename T>
std::pair<const Key, T> map<Key, T>::iterator::operator*() {
  if (AVLTree<Key, T>::Iterator::current_ == nullptr &&
      AVLTree<Key, T>::Iterator::lastNode_ == nullptr) {
    static value_type nothing{};
    return nothing;
  } else if (AVLTree<Key, T>::Iterator::current_ == nullptr &&
             AVLTree<Key, T>::Iterator::lastNode_ != nullptr) {
    AVLTree<Key, T>::Iterator::current_ = AVLTree<Key, T>::Iterator::lastNode_;
  }
  return std::make_pair(AVLTree<Key, T>::Iterator::current_->key_,
                        AVLTree<Key, T>::Iterator::current_->value_);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return iterator(AVLTree<Key, T>::GetMin(AVLTree<Key, T>::root_));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (AVLTree<Key, T>::root_ == nullptr) return begin();

  typename AVLTree<Key, T>::Node* lastNode =
      AVLTree<Key, T>::GetMax(AVLTree<Key, T>::root_);
  iterator last(nullptr, lastNode);
  return last;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& key) {
  typename AVLTree<Key, T>::Node* result =
      AVLTree<Key, T>::SearchNode(AVLTree<Key, T>::root_, key);
  return iterator(result);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    std::pair<const Key, T> pair) {
  std::pair<map<Key, T>::iterator, bool> result(iterator(nullptr), false);
  typename AVLTree<Key, T>::Node* isExist =
      AVLTree<Key, T>::SearchNode(AVLTree<Key, T>::root_, pair.first);
  if (isExist == nullptr) {
    AVLTree<Key, T>::insert(pair.first, pair.second);
    result.first = find(pair.first);
    result.second = true;
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<map<Key, T>::iterator, bool> result(
      iterator(nullptr), false);  // std::make_pair(Iterator(nullptr), false);
  typename AVLTree<Key, T>::Node* isExist =
      AVLTree<Key, T>::SearchNode(AVLTree<Key, T>::root_, key);
  if (isExist == nullptr) {
    AVLTree<Key, T>::insert(key, obj);
    result.first = find(key);
    result.second = true;
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  std::pair<map<Key, T>::iterator, bool> result(
      iterator(nullptr), false);  // std::make_pair(Iterator(nullptr), false);
  typename AVLTree<Key, T>::Node* isExist =
      AVLTree<Key, T>::SearchNode(AVLTree<Key, T>::root_, key);
  if (isExist == nullptr) {
    AVLTree<Key, T>::insert(key, obj);
  } else {
    at(key) = obj;
  }
  result.first = find(key);
  result.second = true;
  return result;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(
       insert(std::forward<Args>(args).first, std::forward<Args>(args).second)),
   ...);
  return result;
}

}  // namespace s21
