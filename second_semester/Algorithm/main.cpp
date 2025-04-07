#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  Quick quick(n);
  quick.print();

  std::cout << std::endl;

  Merge merge(n);
  merge.print();
}
