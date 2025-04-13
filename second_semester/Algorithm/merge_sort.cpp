#include "merge_sort.hpp"
#include "insertion_sort.hpp"
#include <chrono>
using namespace std::chrono;

Merge::Merge() {}

Merge::Merge(std::vector<int> &a) {
  this->array1.assign(a.begin(), a.end());
  this->array2.assign(a.begin(), a.end());

  this->start_merge = high_resolution_clock::now();
  merge_sort(this->array1);
  this->end_merge = high_resolution_clock::now();

  // For analyze threshold value
  // this->insertion_time = InsertionTimed::sort(array2, 0, array2.size());
}

void Merge::merge_sort(std::vector<int> &a) {
  merge_sorted_recursion(a, 0, a.size() - 1);
}

void Merge::merge_sorted_recursion(std::vector<int> &a, int l, int r) {
  if (r - l + 1 <= this->TERMINAL_THRESHOLD) {
    InsertionTimed::sort(a, l, r); // inclusive 範圍
    return;
  }

  if (l < r) {
    int mid = l + (r - l) / 2;
    merge_sorted_recursion(a, l, mid);
    merge_sorted_recursion(a, mid + 1, r);
    merge_sorted_array(a, l, mid, r);
  }
}

void Merge::merge_sorted_array(std::vector<int> &a, int l, int m, int r) {
  int left_length = m - l + 1;
  int right_length = r - m;

  std::vector<int> left_array(left_length);
  std::vector<int> right_array(right_length);

  for (int i = 0; i < left_length; i++)
    left_array[i] = a[l + i];
  for (int i = 0; i < right_length; i++)
    right_array[i] = a[m + 1 + i];

  for (int i = 0, j = 0, k = l; k <= r; k++) {
    if (i < left_length &&
        (j >= right_length || left_array[i] <= right_array[j])) {
      a[k] = left_array[i];
      i++;
    } else {
      a[k] = right_array[j];
      j++;
    }
  }
}

nanoseconds Merge::merge_duration() {
  return duration_cast<nanoseconds>(end_merge - start_merge);
}

nanoseconds Merge::insertion_duration() { return this->insertion_time; }
