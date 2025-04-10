#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <chrono>
#include <iostream>
using namespace std::chrono;

int main() {
  int n;
  std::cin >> n;

  auto start = high_resolution_clock().now();
  Quick quick(n);
  auto end = high_resolution_clock().now();
  auto duration_quick = duration_cast<microseconds>(end - start);
  // quick.print();
  std::cout << duration_quick.count() << std::endl;

  start = high_resolution_clock().now();
  Merge merge(n);
  end = high_resolution_clock().now();
  auto duration_merge = duration_cast<microseconds>(end - start);

  std::cout << duration_quick.count() << std::endl;
  // merge.print();
}
