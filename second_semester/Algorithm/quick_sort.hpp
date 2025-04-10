#pragma once
#include<vector>
#include<chrono>

void insertion_sort(std::vector<int> &);

class Quick{
private:
  std::vector<int> array1, array2;
  std::chrono::high_resolution_clock::time_point start_quick, end_quick;
  std::chrono::high_resolution_clock::time_point start_insertion, end_insertion;

  void swap(int &, int &);
  void quickSort(std::vector<int> &, int, int);
  int quick_partition(std::vector<int> &, int, int);

public: 
  Quick();
  Quick(std::vector<int> &);

  std::chrono::nanoseconds quick_duration();
  std::chrono::nanoseconds insertion_duration();
};

