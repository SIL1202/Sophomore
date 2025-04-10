#include "quick_sort.hpp"
#include <chrono>
using namespace std::chrono;

Quick::Quick() {}

Quick::Quick(std::vector<int> &a) {
  this->array1.assign(a.begin(), a.end());
  this->array2.assign(a.begin(), a.end());

  this->start_quick = high_resolution_clock::now();
  quickSort(array1, 0, a.size() - 1);
  this->end_quick = high_resolution_clock::now();

  this->start_insertion = high_resolution_clock::now();
  insertion_sort(array2);
  this->end_insertion = high_resolution_clock::now();
}

// insertion_sort
void insertion_sort(std::vector<int> &arr) {
  int i, j, key;
  int len = arr.size();
  for (i = 1; i != len; ++i) {
    key = arr[i];
    j = i - 1;
    while ((j >= 0) && (arr[j] > key)) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
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

nanoseconds Quick::quick_duration() {
  return duration_cast<nanoseconds>(end_quick - start_quick);
}

nanoseconds Quick::insertion_duration() {
  return duration_cast<nanoseconds>(end_insertion - start_insertion);
}
