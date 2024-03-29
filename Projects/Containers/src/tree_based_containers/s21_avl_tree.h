#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <limits>

template <typename Key, typename T>
class AVLTree {
 protected:
  class Node;

 public:
  class Iterator;

  using key_type = Key;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = const Iterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* lastNode = nullptr);
    const_reference operator*();
    ~Iterator();
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator!=(const iterator& other) const;
    bool operator==(const iterator& other) const;
    friend class AVLTree<Key, T>;

   protected:
    Node* current_;
    Node* lastNode_;
    iterator& NextNode();
    iterator& PrevNode();
  };

  AVLTree();
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other);
  AVLTree(key_type key, value_type value);
  ~AVLTree();
  AVLTree& operator=(const AVLTree& other);
  AVLTree& operator=(AVLTree&& other);
  std::pair<iterator, bool> insert(key_type key, value_type value);
  void erase(iterator pos);
  bool empty();
  size_type size();
  size_type max_size();
  void merge(AVLTree& other);
  iterator find(const Key& key);
  bool contains(const Key& key);
  void clear();
  void swap(AVLTree& other);
  iterator begin();
  iterator end();
  void PrintTree();
  void DisplayTree();

 protected:
  struct Node {
    key_type key_;
    value_type value_;
    int height_;
    Node* left_;
    Node* right_;
    Node* parent_;

    Node(key_type key, value_type value);
    Node(Node* other);
    bool operator==(Node* other);
    bool operator!=(Node* other);
    friend class AVLTree<Key, T>;
  };
  Node* root_;
  Node* CopyHelper(Node* other, Node* parent);
  void ClearTreeHelper(Node*& node);
  void TraversalHelper(Node* node, int& count);
  void mergeHelper(Node* node);
  void HelpDisplayTree(Node* node, int level);
  int GetHeight(Node* node);
  int GetHeightDiff(Node* node);
  Node* UpdHeight(Node* node);
  static Node* GetMax(Node* node);
  static Node* GetMin(Node* node);
  Node* RightRotation(Node* x);
  Node* LeftRotation(Node* x);
  Node* InsertNode(Node* node, key_type key, value_type value, Node* parent);
  Node* DeleteNode(Node* node, key_type key, value_type value);
  Node* SearchNode(Node* node, key_type key);
  void TraversalTree(Node* node);
  void DestroyTree(Node* node);
};

#include "s21_avl_tree.tpp"

#endif
