#include <iostream>
#include <vector>

struct Element {
  int value;
  int count;
};

std::vector<Element> mergeSortWithCount(std::vector<int> &arr, int left,
                                        int right);
std::vector<Element> countFrequencies(std::vector<int> &arr);

int main() {
  std::vector<int> array{3, 2, 3, 5, 2, 3, 4, 5, 6, 22};
  std::vector<Element> Merged = mergeSortWithCount(array, 0, array.size() - 1);

  bool first = true;
  for (auto &M : Merged) {
    if (!first)
      std::cout << ", ";
    std::cout << "{" << M.value << ", " << M.count << "}";
    first = false;
  }
  return 0;
}

std::vector<Element> mergeSortWithCount(std::vector<int> &arr, int left,
                                        int right) {
  // Base case: single element
  if (left == right) {
    return {{arr[left], 1}};
  }

  // Divide into 2 parts
  int mid = left + (right - left) / 2;

  // Conquer: sort and count each half
  auto leftResult = mergeSortWithCount(arr, left, mid);
  auto rightResult = mergeSortWithCount(arr, mid + 1, right);

  // Merge the results
  std::vector<Element> merged;
  size_t i = 0, j = 0;

  while (i < leftResult.size() && j < rightResult.size()) {
    if (leftResult[i].value < rightResult[j].value) {
      merged.push_back(leftResult[i]);
      i++;
    } else if (leftResult[i].value > rightResult[j].value) {
      merged.push_back(rightResult[j]);
      j++;
    } else {
      // Same value - merge counts
      merged.push_back(
          {leftResult[i].value, leftResult[i].count + rightResult[j].count});
      i++;
      j++;
    }
  }

  // Add remaining elements
  while (i < leftResult.size()) {
    merged.push_back(leftResult[i]);
    i++;
  }

  while (j < rightResult.size()) {
    merged.push_back(rightResult[j]);
    j++;
  }

  return merged;
}

// Wrapper function
std::vector<Element> countFrequencies(std::vector<int> &arr) {
  if (arr.empty())
    return {};
  return mergeSortWithCount(arr, 0, arr.size() - 1);
}
