#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include "node.h"

template <typename T>
class Iterator {
private:
  typedef typename std::vector<T>::iterator iterator;
  iterator current;

public:
  Iterator () {}
  Iterator (iterator current): current(current) {}
  Iterator <T> operator = (iterator other) { return current = other.current; }
  bool operator != (Iterator <T> other) { return &(this -> current) != &(other.current); }
  Iterator <T> operator ++ () { 
    current++;
    return *this;
  }
  Iterator <T> operator -- () {
    current--;
    return *this;
  }
  T operator * () { return *current; }
};

#endif
