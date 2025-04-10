#include "quick_sort.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> generate_random_array(int n) {
  std::vector<int> arr(n);
  for (int &x : arr)
    x = rand(); // or rand() % 10000;
  return arr;
}

int main() {
  int T = 1000;

  for (int n = 2; n <= 50; ++n) {
    std::chrono::nanoseconds total_quick{0}, total_insert{0};

    for (int t = 0; t < T; ++t) {
      std::vector<int> sample = generate_random_array(n);
      Quick sorter(sample);
      total_quick += sorter.quick_duration();
      total_insert += sorter.insertion_duration();
    }

    std::cout << "n = " << n << " | ";
    std::cout << "QuickSort avg: " << (total_quick / T).count() << " ns, ";
    std::cout << "InsertionSort avg: " << (total_insert / T).count() << " ns\n";
    if ((total_quick / T).count() < (total_insert / T).count())
      exit(0);
  }
  return 0;
}
