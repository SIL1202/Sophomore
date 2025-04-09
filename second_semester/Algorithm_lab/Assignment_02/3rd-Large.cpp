#include <algorithm>
#include <iostream>
#include <vector>

typedef double DataType;
std::vector<DataType> given;

struct DataSet {
  size_t begin, count;
};

std::vector<DataType> solve(DataSet input) {
  if (input.count == 1) {
    return {given[input.begin]};
  }

  DataSet left, right;
  left.begin = input.begin;
  left.count = input.count / 2;
  right.begin = input.begin + left.count;
  right.count = input.count - left.count;

  auto leftMax = solve(left);
  auto rightMax = solve(right);

  std::vector<DataType> merged;
  merged.insert(merged.end(), leftMax.begin(), leftMax.end());
  merged.insert(merged.end(), rightMax.begin(), rightMax.end());

  std::sort(merged.begin(), merged.end(), std::greater<DataType>());
  if (merged.size() > 3) {
    merged.resize(3);
  }
  return merged;
}

int main() {
  given = {5, 33, 3, 45, 8, 9, 2, 1, 7, 0, 55};
  DataSet data = {0, given.size()};

  auto top3 = solve(data);

  std::cout << "Top 3 elements: ";
  for (auto num : top3) {
    std::cout << num << " ";
  }
  return 0;
}
