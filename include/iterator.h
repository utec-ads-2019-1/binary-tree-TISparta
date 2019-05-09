#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdexcept>
#include <exception>
#include <vector>
#include "node.h"

template <typename T>
class Iterator {
private:
  typedef typename std::vector<T>::iterator iterator;
  iterator current;
  iterator begin, end;

public:
  Iterator () {}
  Iterator (iterator current, iterator begin, iterator end):
            current(current), begin(begin), end(end) {}
  Iterator <T> operator = (iterator other) { return current = other.current; }
  bool operator != (Iterator <T> other) { return this -> current != other.current; }
  Iterator <T> operator ++ () { 
    if (not (current != end)) {
      throw std::out_of_range("The iterator is out of range");
    }
    current++;
    return *this;
  }
  Iterator <T> operator -- () {
    if (not (current != begin)) {
      throw std::out_of_range("The iterator is out of range");
    }
    current--;
    return *this;
  }
  T operator * () { return *current; }
};

#endif
