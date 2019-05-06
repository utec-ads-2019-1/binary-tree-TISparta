#ifndef TESTER_H
#define TESTER_H

#include "mocker.h"
#include "bstree.h"

#define NUMBER_OF_TESTS 1000

class Tester {
private:
  template <typename T>
  static void testBSTree (Mocker, std::vector <T>);

  template <typename T>
  static void sortAndPrune (std::vector <T> &);

public:
  static void execute ();
};

#endif
