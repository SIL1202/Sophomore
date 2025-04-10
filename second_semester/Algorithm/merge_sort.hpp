#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP
#include <vector>

class Merge{
  private:
    std::vector<int> array;
    void merge_sort(std::vector<int> &);
    void merge_sorted_array(std::vector<int> &, int, int, int);
    void merge_sorted_recursion(std::vector<int> &, int, int);
  
  public:
    Merge();
    Merge(int, std::vector<int> &);

    void print();  
};

#endif
