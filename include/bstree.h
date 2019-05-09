#ifndef BSTREE_H
#define BSTREE_H

#include <cassert>
#include <vector>
#include "node.h"
#include "iterator.h"

template <typename T>
class BSTree {
private:
  Node <T>* root;
  std::vector <T> preorder, inorder, postorder;

  bool find (const T& data, const Node <T>* current) const {
    if (not current) return false;
    if (data < current -> data) return find(data, current -> left);
    if (current -> data < data) return find(data, current -> right);
    return true;
  }

  bool insert (const T& data, Node <T>*& current) {
    if (not current) {
      current = new Node <T> (data);
      return true;
    }
    if (data < current -> data) return insert(data, current -> left);
    if (current -> data < data) return insert(data, current -> right);
    return false; 
  }

  T findMin (const T& data, const Node <T>* current) const {
    assert(current); // Este metodo no se llamará en BSTree degenerados
    if (not current -> left) return current -> data;
    return findMin(data, current -> left);
  }

  bool remove (const T& data, Node <T>*& current) {
    if (not current) return false;
    if (data < current -> data) return remove(data, current -> left);
    if (current -> data < data) return remove(data, current -> right);
    // 2 hijos
    if (current -> left and current -> right) {
      current -> data = findMin(data, current -> right);
      return remove(current -> data, current -> right);
      // Tambien podriamos hacer algo asi
      // current -> data = findMax(data, current -> left);
      // return remove(current -> data, current -> left);
    }
    // 1 hijo
    Node <T>* pib = current;
    current = (current -> left) ? current -> left : current -> right;
    delete pib;
    return true;
  }

  unsigned int size (const Node <T>* current) const {
    if (not current) return 0;
    return 1 + size(current -> left) + size(current -> right);
  }

  void goPreorder (const Node <T>* current) {
    if (not current) return;
    preorder.push_back(current -> data);
    goPreorder(current -> left);
    goPreorder(current -> right);
  }

  void goInorder (const Node <T>* current) {
    if (not current) return;
    goInorder(current -> left);
    inorder.push_back(current -> data);
    goInorder(current -> right);
  }

  void goPostorder (const Node <T>* current) {
    if (not current) return;
    goPostorder(current -> left);
    goPostorder(current -> right);
    postorder.push_back(current -> data);
  }

  void printOrder (const std::vector <T>& order) {
    for (auto elem: order) std::cout << elem << ' ';
    std::cout << '\n';
  }

  void clear (Node <T>*& current) {
    if (not current) return;
    clear(current -> left);
    clear(current -> right);
    delete current;
  }

public:

  BSTree(): root(nullptr) {};

  bool find (const T data) const { return find(data, root); }

  bool insert (const T data) { return insert(data, root); }

  bool remove (const T data) { return remove(data, root); }

  unsigned int size () const { return size(root); }

  void traversePreOrder (bool print = false) {
    preorder.clear();
    goPreorder(root);
    if (print) printOrder(preorder);
  }

  void traverseInOrder (bool print = false) {
    inorder.clear();
    goInorder(root);
    if (print) printOrder(inorder);
  }

  void traversePostOrder (bool print = false) {
    postorder.clear();
    goPostorder(root);
    if (print) printOrder(postorder);
  }

  Iterator <T> begin () {
    traverseInOrder();
    return Iterator <T> (std::begin(inorder), std::begin(inorder), std::end(inorder));
  }

  Iterator <T> end () {
    traverseInOrder();
    return Iterator <T> (std::end(inorder), std::begin(inorder), std::end(inorder));
  }

  ~BSTree () {
    clear(root);
  }
};

#endif
