#ifndef MOCKER_H
#define MOCKER_H

#include <random>
#include <type_traits>

#define MIN 0
#define MAX 100

class Mocker {
private:
  std::mt19937 rng;

public:
  Mocker() { rng.seed(std::random_device()()); }

  int generateRandomInt (int min = MIN, int max = MAX);
  char generateRandomChar ();

  template <typename T>
  T* generateRandomArray (unsigned int size) {
    T* elements = new T[size];
    for (int i = 0; i < size; i++) {
      if (std::is_same <T, int>::value) {
        elements[i] = generateRandomInt();
      } else if (std::is_same <T, char>::value) {
        elements[i] = generateRandomChar();
      }
    }

    return elements;
  }
};

#endif
