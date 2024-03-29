#include "s21_avl_tree.h"

// CLASS NODE

template <typename Key, typename T>
AVLTree<Key, T>::Node::Node(Key key, T value)
    : key_(key),
      value_(value),
      height_(1),
      left_(nullptr),
      right_(nullptr),
      parent_(nullptr){};

template <typename Key, typename T>
AVLTree<Key, T>::Node::Node(Node* other)
    : key_(other->key_),
      value_(other->value_),
      height_(other->height_),
      left_(other->left_),
      right_(other->right_),
      parent_(other->parent_){};

template <typename Key, typename T>
bool AVLTree<Key, T>::Node::operator==(Node* other) {
  return (key_ == other.key_ && value_ == other.value_);
}

template <typename Key, typename T>
bool AVLTree<Key, T>::Node::operator!=(Node* other) {
  return (key_ != other.key_ && value_ != other.value_);
}

// CLASS ITERATOR
template <typename Key, typename T>
AVLTree<Key, T>::Iterator::Iterator() : current_(nullptr), lastNode_(nullptr) {}

template <typename Key, typename T>
AVLTree<Key, T>::Iterator::Iterator(Node* node, Node* lastNode)
    : current_(node), lastNode_(lastNode) {}

template <typename Key, typename T>
const T& AVLTree<Key, T>::Iterator::operator*() {
  if (current_ == nullptr && lastNode_ == nullptr) {
    static T nothing{};
    return nothing;
  } else if (current_ == nullptr && lastNode_ != nullptr) {
    current_ = lastNode_;
  }
  return current_->key_;
}

template <typename Key, typename T>
AVLTree<Key, T>::Iterator::~Iterator() {
  if (current_) {
    current_ = nullptr;
  }
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator&
AVLTree<Key, T>::Iterator::operator++() {
  if (lastNode_ == nullptr || (lastNode_ != nullptr && current_ != nullptr &&
                               lastNode_->key_ < current_->key_)) {
    lastNode_ = current_;
  }
  NextNode();
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator
AVLTree<Key, T>::Iterator::operator++(int) {
  Iterator temp = *this;
  if (temp == nullptr) {
    Iterator n(lastNode_);
    *this = n;
  }
  operator++();
  return temp;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator&
AVLTree<Key, T>::Iterator::operator--() {
  if (lastNode_ == nullptr || (lastNode_ != nullptr && current_ != nullptr &&
                               lastNode_->key_ < current_->key_)) {
    lastNode_ = current_;
  }
  PrevNode();
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator
AVLTree<Key, T>::Iterator::operator--(int) {
  Iterator temp = *this;
  if (temp == nullptr) {
    Iterator n(lastNode_);
    *this = n;
  }
  operator--();
  return temp;
}

template <typename Key, typename T>
bool AVLTree<Key, T>::Iterator::operator!=(const Iterator& other) const {
  return current_ != other.current_;
}

template <typename Key, typename T>
bool AVLTree<Key, T>::Iterator::operator==(const Iterator& other) const {
  return current_ == other.current_;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator&
AVLTree<Key, T>::Iterator::NextNode() {
  if (current_ == nullptr) {
    return *this;
  }
  if (current_->right_ != nullptr) {
    current_ = current_->right_;
    current_ = GetMin(current_);
  } else {
    Node* parent = current_->parent_;
    while (parent != nullptr && current_ == parent->right_) {
      current_ = parent;
      parent = parent->parent_;
    }
    current_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator::Iterator&
AVLTree<Key, T>::Iterator::PrevNode() {
  if (current_ == nullptr) {
    return *this;
  }
  if (current_->left_ != nullptr) {
    current_ = current_->left_;
    current_ = GetMax(current_);
  } else {
    Node* parent = current_->parent_;
    while (parent != nullptr && current_ == parent->left_) {
      current_ = parent;
      parent = parent->parent_;
    }
    current_ = parent;
  }
  return *this;
}

// CLASS AVLTree

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree() : root_(nullptr){};

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree(Key key, T value) : root_(new Node(key, value)){};

template <typename Key, typename T>
AVLTree<Key, T>::~AVLTree() {
  ClearTreeHelper(root_);
};

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::CopyHelper(Node* other,
                                                            Node* parent) {
  if (other == nullptr) {
    return nullptr;
  }
  Node* newNode = new Node(other->key_, other->value_);
  newNode->height_ = other->height_;
  newNode->parent_ = parent;
  newNode->left_ = CopyHelper(other->left_, newNode);
  newNode->right_ = CopyHelper(other->right_, newNode);
  return newNode;
}

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree(const AVLTree& other) {
  root_ = CopyHelper(other.root_, nullptr);
}

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree(AVLTree&& other) {
  swap(other);
  other.root_ = nullptr;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTree& AVLTree<Key, T>::operator=(
    const AVLTree& other) {
  if (this != &other) {
    DestroyTree();
    root_ = CopyHelper(other, nullptr);
  }
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTree& AVLTree<Key, T>::operator=(AVLTree&& other) {
  if (this != &other) {
    swap(other);
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
void AVLTree<Key, T>::ClearTreeHelper(Node*& node) {
  if (node != nullptr) {
    ClearTreeHelper(node->left_);
    ClearTreeHelper(node->right_);
    delete node;
  }
}

template <typename Key, typename T>
void AVLTree<Key, T>::HelpDisplayTree(Node* node, int level) {
  if (node == nullptr) {
    return;
  }
  HelpDisplayTree(node->right_, level + 1);

  for (int i = 0; i < level; i++) {
    std::cout << "\t";
  }
  std::cout << node->key_ << "(" << node->value_ << ")" << std::endl;
  HelpDisplayTree(node->left_, level + 1);
}

template <typename Key, typename T>
int AVLTree<Key, T>::GetHeight(Node* node) {
  return node ? node->height_ : 0;
}

template <typename Key, typename T>
int AVLTree<Key, T>::GetHeightDiff(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return GetHeight(node->left_) - GetHeight(node->right_);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::UpdHeight(Node* node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
  return node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::GetMax(Node* node) {
  if (node == nullptr || node->right_ == nullptr) {
    return node;
  }
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::GetMin(Node* node) {
  if (node == nullptr || node->left_ == nullptr) {
    return node;
  }
  return GetMin(node->left_);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::RightRotation(Node* x) {
  Node* y = x->left_;
  Node* xL = y->right_;
  Node* xP = x->parent_;
  y->parent_ = xP;
  y->right_ = x;
  x->parent_ = y;
  if (xL) {
    xL->parent_ = x;
  }
  x->left_ = xL;
  x = UpdHeight(x);
  y = UpdHeight(y);

  return y;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::LeftRotation(Node* x) {
  Node* y = x->right_;
  Node* xR = y->left_;
  Node* xP = x->parent_;
  y->parent_ = xP;
  y->left_ = x;
  x->parent_ = y;
  if (xR) {
    xR->parent_ = x;
  }
  x->right_ = xR;

  x = UpdHeight(x);
  y = UpdHeight(y);
  return y;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::InsertNode(Node* node, Key key,
                                                            T value,
                                                            Node* parent) {
  if (node == nullptr) {
    Node* newNode = new Node(key, value);
    newNode->parent_ = parent;
    return newNode;
  }

  if (key < node->key_) {
    node->left_ = InsertNode(node->left_, key, value, node);
  } else {
    node->right_ = InsertNode(node->right_, key, value, node);
  }

  node = UpdHeight(node);
  int balance = GetHeightDiff(node);
  if (balance > 1 && key < node->left_->key_) {
    node = RightRotation(node);
  } else if (balance < -1 && key > node->right_->key_) {
    node = LeftRotation(node);
  } else if (balance > 1 && key > node->left_->key_) {
    node->left_ = LeftRotation(node->left_);
    node = RightRotation(node);
  } else if (balance < -1 && key < node->right_->key_) {
    node->right_ = RightRotation(node->right_);
    node = LeftRotation(node);
  }
  return node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::SearchNode(Node* node,
                                                            Key key) {
  if (node == nullptr || node->key_ == key) {
    return node;
  }
  if (key < node->key_) {
    node = SearchNode(node->left_, key);
  } else {
    node = SearchNode(node->right_, key);
  }
  return node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Node* AVLTree<Key, T>::DeleteNode(Node* node, Key key,
                                                            T value) {
  if (node == nullptr) {
    return node;
  }
  if (key < node->key_)
    node->left_ = DeleteNode(node->left_, key, value);
  else if (key > node->key_)
    node->right_ = DeleteNode(node->right_, key, value);
  else {
    if ((node->left_ == nullptr) || (node->right_ == nullptr)) {
      Node* temp = node->left_ ? node->left_ : node->right_;

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      Node* maxLn = GetMax(node->left_);
      node->key_ = maxLn->key_;
      node->value_ = maxLn->value_;
      node->left_ = DeleteNode(node->left_, maxLn->key_, maxLn->value_);
    }
  }

  if (node != nullptr) {
    node = UpdHeight(node);
    int balance = GetHeightDiff(node);

    if (balance > 1 && GetHeightDiff(node->left_) >= 0) {
      node = RightRotation(node);
    }
    if (balance < -1 && GetHeightDiff(node->right_) <= 0) {
      node = LeftRotation(node);
    } else if (balance > 1 && GetHeightDiff(node->left_) < 0) {
      node->left_ = LeftRotation(node->left_);
      node = RightRotation(node);
    } else if (balance < -1 && GetHeightDiff(node->right_) > 0) {
      node->right_ = RightRotation(node->right_);
      node = LeftRotation(node);
    }
  }
  return node;
}

template <typename Key, typename T>
std::pair<typename AVLTree<Key, T>::Iterator, bool> AVLTree<Key, T>::insert(
    Key key, T value) {
  std::pair<Iterator, bool> result;
  root_ = InsertNode(root_, key, value, nullptr);
  result.first = find(key);
  result.first.current_ ? result.second = true : result.second = false;
  return result;
}

template <typename Key, typename T>
void AVLTree<Key, T>::erase(Iterator pos) {
  if (root_ != nullptr && pos != nullptr) {
    Key key = pos.current_->key_;
    Node* delNode = SearchNode(root_, key);
    if (delNode != nullptr) {
      root_ = DeleteNode(root_, key, delNode->value_);
    }
  }
}

template <typename Key, typename T>
void AVLTree<Key, T>::TraversalTree(Node* node) {
  if (node == nullptr) {
    return;
  }
  TraversalTree(node->left_);
  std::cout << node->key_ << " ";
  TraversalTree(node->right_);
}

template <typename Key, typename T>
void AVLTree<Key, T>::PrintTree() {
  TraversalTree(root_);
  std::cout << std::endl;
}

template <typename Key, typename T>
void AVLTree<Key, T>::DisplayTree() {
  HelpDisplayTree(root_, 0);
}

template <typename Key, typename T>
void AVLTree<Key, T>::DestroyTree(Node* node) {
  if (node == nullptr) {
    return;
  }
  DestroyTree(node->left_);
  DestroyTree(node->right_);
  delete node;
}

template <typename Key, typename T>
bool AVLTree<Key, T>::empty() {
  return root_ ? false : true;
}

template <typename Key, typename T>
size_t AVLTree<Key, T>::size() {
  int count = 0;
  TraversalHelper(root_, count);
  return count;
}

template <typename Key, typename T>
size_t AVLTree<Key, T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(Node);
}

template <typename Key, typename T>
void AVLTree<Key, T>::merge(AVLTree& other) {
  mergeHelper(other.root_);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::find(const Key& key) {
  Node* result = SearchNode(root_, key);
  return Iterator(result);
}

template <typename Key, typename T>
bool AVLTree<Key, T>::contains(const Key& key) {
  Node* existNode = SearchNode(root_, key);
  return !(existNode == nullptr);
}

template <typename Key, typename T>
void AVLTree<Key, T>::clear() {
  ClearTreeHelper(root_);
  root_ = nullptr;
}

template <typename Key, typename T>
void AVLTree<Key, T>::swap(AVLTree& other) {
  Node* tmp = other.root_;
  other.root_ = root_;
  root_ = tmp;
}

template <typename Key, typename T>
void AVLTree<Key, T>::TraversalHelper(Node* node, int& count) {
  if (node != nullptr) {
    TraversalHelper(node->left_, count);
    count++;
    TraversalHelper(node->right_, count);
  }
}

template <typename Key, typename T>
void AVLTree<Key, T>::mergeHelper(Node* node) {
  if (node != nullptr) {
    mergeHelper(node->left_);
    mergeHelper(node->right_);
    root_ = InsertNode(root_, node->key_, node->value_, root_);
  }
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::begin() {
  return Iterator(GetMin(root_));
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::end() {
  if (root_ == nullptr) return begin();
  Node* lastNode = GetMax(AVLTree<Key, T>::root_);
  Iterator last(nullptr, lastNode);
  return last;
}
