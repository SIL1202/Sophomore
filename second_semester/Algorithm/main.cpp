#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> generate_random_array(int);
void QuickSort_with_InsertionSort(std::vector<int> &);
void MergeSort_with_InsertionSort(std::vector<int> &);

int main() {
  std::vector<int> array1, array2;
  for (int i = 2; i <= 40; i++) {
    int t = i;
    array1.push_back(t);
  }
  for (int i = 48; i <= 60; i++) {
    int t = i * 10;
    array2.push_back(t);
  }
  QuickSort_with_InsertionSort(array1);
  std::cout << std::endl;
  MergeSort_with_InsertionSort(array2);
  return 0;
}

std::vector<int> generate_random_array(int n) {
  std::vector<int> arr(n);
  for (int &x : arr)
    x = rand(); // or rand() % 10000;
  return arr;
}

void QuickSort_with_InsertionSort(std::vector<int> &inputSizes) {
  for (int n : inputSizes) {
    std::chrono::nanoseconds total_quick{0}, total_insert{0};
    std::vector<int> sample = generate_random_array(n);
    Quick sorter(sample);
    std::chrono::nanoseconds Quick = sorter.quick_duration();
    std::chrono::nanoseconds Insertion = sorter.insertion_duration();

    std::cout << "n = " << n << " | ";
    std::cout << "QuickSort " << Quick.count() << " ns, ";
    std::cout << "InsertionSort " << Insertion.count() << " ns\n";
  }
}

void MergeSort_with_InsertionSort(std::vector<int> &inputSizes) {
  for (int n : inputSizes) { // the time when n is difference size.
    std::chrono::nanoseconds total_quick{0}, total_insert{0};
    std::vector<int> sample = generate_random_array(n);
    Merge sorter(sample);
    std::chrono::nanoseconds Merge = sorter.merge_duration();
    std::chrono::nanoseconds Insertion = sorter.insertion_duration();

    std::cout << "n = " << n << " | ";
    std::cout << "MergeSort " << Merge.count() << " ns, ";
    std::cout << "InsertionSort " << Insertion.count() << " ns\n";
    // if (Merge.count() < Insertion.count())
    //   exit(0);
  }
}
