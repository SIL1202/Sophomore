#include <algorithm>
#include <iostream>
#include <vector>

// C = {1, 5, 10}
// m = 18
typedef std::vector<int> IntList;

IntList change_making(IntList &C, int m) {
  IntList A(C.size(), 0); // store how many coin in the corresponding value
  std::sort(C.begin(), C.end());
  // Try coins throw max to min
  for (size_t i = C.size() - 1; m > 0 && i >= 0;) {
    if (C[i] <= m) {
      ++A[i];
      m -= C[i];
    } else
      --i;
  }
  // no way to combine specified amount, return nothing
  if (m > 0)
    A.clear();
  return A;
}

int main() {
  std::vector<int> C = {1, 5, 10, 50};
  int m = 9;

  std::vector<int> ans = change_making(C, m);
  for (int v : ans) {
    std::cout << v << " ";
  }
}
