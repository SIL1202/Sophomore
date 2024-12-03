#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

template <class T> class MinMaxHeap {
public:
  MinMaxHeap() {}

  // Insert a new element into the heap and maintain Min-Max Heap properties
  void insert(T value) {
    data.push_back(value);
    heapifyUp(data.size() - 1);
  }

  // Retrieve the minimum element in the heap (at root for Min-Max Heap)
  T getMin() const {
    if (data.empty()) {
      throw std::out_of_range("Heap is empty.");
    }
    return data[0]; // 根節點為最小節點
  } // min-level越往下會越大

  // Retrieve the maximum element in the heap
  T getMax() const {
    if (data.empty()) {
      throw std::out_of_range("Heap is empty.");
    }
    // max-level越往下會越小
    // 所以比較最上面的三個點就好
    if (data.size() == 1)
      return data[0];
    if (data.size() == 2)
      return data[1];
    return std::max(data[1], data[2]);
  }

  // Delete the minimum element (at root) and maintain Min-Max Heap properties
  void deleteMin() {
    if (data.empty()) {
      throw std::out_of_range("Heap is empty.");
    }
    data[0] = data.back();
    data.pop_back();
    heapifyDown(0);
  }

  // Delete the maximum element and maintain Min-Max Heap properties
  void deleteMax() {
    if (data.empty()) {
      throw std::out_of_range("Heap is empty.");
    }
    int maxIndex = (data.size() == 2 || data[1] > data[2]) ? 1 : 2;
    data[maxIndex] = data.back();
    data.pop_back();
    heapifyDown(maxIndex);
  }

private:
  std::vector<T> data;

  // Helper function to maintain Min-Max Heap property when inserting
  void heapifyUp(int index) {
    if (index == 0)
      return;

    int parentIndex = (index - 1) / 2;

    // Determine if the current level is a min or max min-level
    // 1.查看是否在min-level
    // 2.將值與parent比較
    // 3.再將值與該層的grandparent比較
    // 4.完成交換
    if (isMinLevel(index)) {
      if (data[index] > data[parentIndex]) {
        std::swap(data[index], data[parentIndex]);
        heapifyUpMax(parentIndex);
      } else {
        heapifyUpMin(index);
      }
    } else {
      if (data[index] < data[parentIndex]) {
        std::swap(data[index], data[parentIndex]);
        heapifyUpMin(parentIndex);
      } else {
        heapifyUpMax(index);
      }
    }
  }

  void heapifyUpMin(int index) {
    int grandparentIndex = (index - 3) / 4;
    if (index > 2 && data[index] < data[grandparentIndex]) {
      std::swap(data[index], data[grandparentIndex]);
      heapifyUpMin(grandparentIndex);
    }
  }

  void heapifyUpMax(int index) {
    int grandparentIndex = (index - 3) / 4;
    if (index > 2 && data[index] > data[grandparentIndex]) {
      std::swap(data[index], data[grandparentIndex]);
      heapifyUpMax(grandparentIndex);
    }
  }

  void heapifyDown(int index) {
    if (isMinLevel(index)) {
      heapifyDownMin(index);
    } else {
      heapifyDownMax(index);
    }
  }

  void heapifyDownMin(int index) {
    int size = data.size();
    int minIndex = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Find the minimum among current node and children
    if (leftChild < size && data[leftChild] < data[minIndex])
      minIndex = leftChild;
    if (rightChild < size && data[rightChild] < data[minIndex])
      minIndex = rightChild;

    if (minIndex != index) {
      std::swap(data[index], data[minIndex]);
      heapifyDown(minIndex);
    }
  }

  void heapifyDownMax(int index) {
    int size = data.size();
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Find the maximum among current node and children
    if (leftChild < size && data[leftChild] > data[maxIndex])
      maxIndex = leftChild;
    if (rightChild < size && data[rightChild] > data[maxIndex])
      maxIndex = rightChild;

    if (maxIndex != index) {
      std::swap(data[index], data[maxIndex]);
      heapifyDown(maxIndex);
    }
  }

  bool isMinLevel(int index) const {
    int level = 0;
    while (index > 0) {
      index = (index - 1) / 2; // 這樣可以從子節點回到父節點
      level++;
    }
    return level % 2 == 0;
  }
};

int main() {
  MinMaxHeap<int> mmHeap;
  int j;
  srand(time(NULL));

  // Insert random elements
  for (j = 0; j < 10; j++) {
    mmHeap.insert(rand() % 100);
  }

  // Print and delete min elements
  while (true) {
    try {
      std::cout << mmHeap.getMin() << " ";
      mmHeap.deleteMin();
    } catch (std::exception &) {
      break;
    }
  }
  std::cout << std::endl;

  // Insert random elements
  for (j = 0; j < 10; j++) {
    mmHeap.insert(rand() % 100);
  }

  // Print and delete max elements
  while (true) {
    try {
      std::cout << mmHeap.getMax() << " ";
      mmHeap.deleteMax();
    } catch (std::exception &) {
      break;
    }
  }

  return 0;
};
