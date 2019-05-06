#include <iostream>
#include <algorithm>
#include "tester.h"
#include "color.h"

struct Test {
  const int WIDTH = 50;
  int passed = 0;
  int failed = 0;
  Test () {}
  void init (int nTest) {
    std::cout << Color::blue << Color::underline <<
      "Running test " << nTest << std::endl << Color::normal;
    passed = failed = 0;
  }
  void check (bool condition, const std::string& msg) {
    if (condition) {
      passed++;
      std::cout << Color::green << Color::bold << "OK" << std::endl << Color::normal;
    } else {
      failed++;
      std::cout << Color::red << Color::bold << "!OK" << std::endl << Color::normal;
    }
  }
  void print (const std::string& msg) {
    const std::string pad(WIDTH, '#');
    const int left = (WIDTH - int(msg.size())) / 2;
    const int right = WIDTH - int(msg.size()) - left;
    const std::string lspaces(left, ' ');
    const std::string rspaces(right, ' ');
    std::cout << Color::yellow << Color::bold;
    std::cout << pad << std::endl;
    std::cout << lspaces << msg << rspaces << '\n';
    std::cout << pad << std::endl;
    std::cout << Color::normal;
  }
  void showResults () {
    std::cout << Color::blue << Color::bold << Color::underline << "Results\n" << Color::normal;
    std::cout << Color::blue << Color::bold << "Passed " << passed << std::endl << Color::normal;
    std::cout << Color::blue << Color::bold << "Failed " << failed << std::endl << Color::normal;
    print("TESTS FINISHED" );
  }
} tester;


void Tester::execute () {
  tester.print("Binary Search Tree Practice");
  Mocker mocker;
  for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
    tester.init(i + 1);
    unsigned int size = mocker.generateRandomInt(10);
    int* elements = mocker.generateRandomArray <int> (size);
    testBSTree <int> (mocker, std::vector <int> (elements, elements + size));
  }
}

template <typename T>
void Tester::testBSTree (Mocker mocker, std::vector <T> elements) {
  BSTree <T>* test = new BSTree <T>;
  for (int j = 0; j < int(elements.size()); ++j) {
    test -> insert(elements[j]);
    tester.check(test -> find(elements[j]), "There is a problem with the insert or find");
  }
  sortAndPrune(elements);

  tester.check(elements.size() == test -> size(), "There is a problem with the insert or size");

  unsigned int toRemove = mocker.generateRandomInt(1, elements.size());
  for (int j = 0; j < int(toRemove); ++j) {
    unsigned int index = mocker.generateRandomInt(0, elements.size() - 1);
    T temp = elements.at(index);
    elements.erase(elements.begin() + index);
    test -> remove(temp);
    tester.check(!test -> find(temp), "There is a problem with the remove or find");
  }

  tester.check(elements.size() == test -> size(), "There is a problem with the remove or size");
  
  auto it = test -> begin();

  for (int j = 0; j < int(elements.size()) && it != test -> end(); ++j) {
    tester.check(elements.at(j) == *it, "There is a problem with the iterator (++)");
    ++it;
  }

  for (int j = elements.size() - 1; j >= 0; --j) {
    --it;
    tester.check(elements.at(j) == *it, "There is a problem with the iterator (--)");
  }
}

template <typename T>
void Tester::sortAndPrune (std::vector <T>& array) {
  sort(array.begin(), array.end());
  auto last = unique(array.begin(), array.end());
  array.erase(last, array.end());
}
