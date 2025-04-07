#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP
#include<vector>

class Quick{
private:
  std::vector<int> array;
  void swap(int &, int &);
  void quickSort(std::vector<int> &, int, int);
  int quick_partition(std::vector<int> &, int, int);

public: 
  Quick();
  Quick(int);

  void print();
};

#endif
