#ifndef NODE_H
#define NODE_H

template <typename T>
class BSTree;

template <typename T>
class Iterator;

#include <iostream>

template <typename T>
class Node {
private:
  T data;
  Node <T>* left = 0;
  Node <T>* right = 0;

  Node (T data): data(data) {}
  
  template <class>
  friend class BSTree;

  template <class>
  friend class Iterator;
};

#endif
