#pragma once
#include<vector>
#include<chrono>

class Quick{
private:
  std::vector<int> array1, array2;
  std::chrono::high_resolution_clock::time_point start_quick, end_quick;
  std::chrono::nanoseconds insertion_time;
  const int TERMINAL_THRESHOLD = 40;

  void swap(int &, int &);
  void quickSort(std::vector<int> &, int, int);
  int quick_partition(std::vector<int> &, int, int);

public: 
  Quick();
  Quick(std::vector<int> &);

  std::chrono::nanoseconds quick_duration() const;
  std::chrono::nanoseconds insertion_duration() const;
};

