#include "quick_sort.hpp"
#include <iostream>

Quick::Quick() {}

Quick::Quick(int n) : array(n) {
  for (int i = 0; i < n; i++)
    array[i] = n - i;

  quickSort(array, 0, n - 1);
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

  // 記錄當前範圍內的數組、pivot 位置、遞迴深度
  std::vector<int> temp(array.begin() + low, array.begin() + high + 1);

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

void Quick::print() {
  for (int s : Quick::array)
    std::cout << s << " ";
}
// Print function
