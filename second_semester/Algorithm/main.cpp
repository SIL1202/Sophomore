#include "quick_sort.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> generate_random_array(int);
int main() {
  int T = 1000;

  for (int n = 2; n <= 100; ++n) {
    std::chrono::nanoseconds total_quick{0}, total_insert{0};
    std::vector<int> sample = generate_random_array(n);
    Quick sorter(sample);
    std::chrono::nanoseconds Quick = sorter.quick_duration();
    std::chrono::nanoseconds Insertion = sorter.insertion_duration();

    std::cout << "n = " << n << " | ";
    std::cout << "QuickSort " << Quick.count() << " ns, ";
    std::cout << "InsertionSort " << Insertion.count() << " ns\n";

/*     if (Quick < Insertion)
      break;
  */ }

return 0;
}

std::vector<int> generate_random_array(int n) {
  std::vector<int> arr(n);
  for (int &x : arr)
    x = rand(); // or rand() % 10000;
  return arr;
}
