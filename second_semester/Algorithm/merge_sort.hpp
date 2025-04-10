#pragma once
#include <vector>
#include <chrono>

void insertion_sort(std::vector<int> &);

class Merge{
  private:
    std::vector<int> array1, array2;
    std::chrono::high_resolution_clock::time_point start_merge, end_merge;
    std::chrono::nanoseconds insertion_time;
        

    void merge_sort(std::vector<int> &);
    void merge_sorted_array(std::vector<int> &, int, int, int);
    void merge_sorted_recursion(std::vector<int> &, int, int);
  
  public:
    Merge();
    Merge(std::vector<int> &);

    std::chrono::nanoseconds merge_duration();
    std::chrono::nanoseconds insertion_duration();
};

