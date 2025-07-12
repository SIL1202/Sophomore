#include "quick_sort.hpp"
#include "insertion_sort.hpp"
#include <chrono>
using namespace std::chrono;

Quick::Quick() {}

Quick::Quick(std::vector<int> &a) {
  this->array1.assign(a.begin(), a.end());
  this->array2.assign(a.begin(), a.end());

  this->start_quick = high_resolution_clock::now();
  quickSort(array1, 0, a.size() - 1);
  this->end_quick = high_resolution_clock::now();

  // For analyze threshold value
  // this->insertion_time = InsertionTimed::sort(array2, 0, array2.size() - 1);
}

void Quick::swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

// QuickSort
void Quick::quickSort(std::vector<int> &array, int low, int high) {
  if (low >= high) {
    return;
  }
  if (high - low + 1 <= this->TERMINAL_THRESHOLD) {
    InsertionTimed::sort(array, low, high); // <-- inclusive 範圍
    return;
  }

  int pivot = quick_partition(array, low, high);
  quickSort(array, low, pivot - 1);
  quickSort(array, pivot + 1, high);
}

// Partition
int Quick::quick_partition(std::vector<int> &array, int low, int high) {
  int pivot_value = array[high];
  int i = low;
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot_value) {
      swap(array[i], array[j]);
      i++;
    }
  }
  swap(array[i], array[high]);
  return i;
}

nanoseconds Quick::quick_duration() const {
  return duration_cast<nanoseconds>(end_quick - start_quick);
}

nanoseconds Quick::insertion_duration() const { return this->insertion_time; }
