#include <algorithm>
#include <limits>
#include <vector>

int find_min_small(const std::vector<int> &arr, int low,
                   int high); // declaration
// *** You need to complete this function ***
// *** 你需要完成這個函數 ***
int find_min_dc(const std::vector<int> &arr, int low, int high) {
  // Base case: when range size <= 3, call the provided function
  // 基礎情況：當區間大小 <= 3 時，調用提供的函數
  const int THRESHOLD = 3;
  if (high - low + 1 <= THRESHOLD) {
    return find_min_small(arr, low, high);
  }

  int mid = low + (high - low) / 2;
  // Divide: calculate the midpoint
  // 分解：計算中間點
  // TODO: Calculate mid / 計算 mid
  // int mid = low + (high - low) / 2; // Example calculation / 計算範例

  int leftmost = find_min_dc(arr, low, mid);
  int rightmost = find_min_dc(arr, mid + 1, high);
  // Conquer: recursively find the minimum in left and right sub-ranges
  // 解決：遞迴找出左右子區間的最小值
  // TODO: Recursively call find_min_dc for the left half (min_left)
  // TODO: 遞迴呼叫 find_min_dc 找出左半邊的最小值 (min_left)
  // int min_left = find_min_dc(arr, low, mid); // Example call / 呼叫範例

  // TODO: Recursively call find_min_dc for the right half (min_right)
  // TODO: 遞迴呼叫 find_min_dc 找出右半邊的最小值 (min_right)
  // int min_right = find_min_dc(arr, mid + 1, high); // Example call / 呼叫範例

  // Combine: compare the minimums from left and right
  // 合併：比較左右子區間的最小值
  // TODO: Return the smaller of min_left and min_right
  // TODO: 返回 min_left 和 min_right 中的較小者
  // return std::min(min_left, min_right); // Example combination / 合併範例
  return std::min(leftmost, rightmost);
}

// --- Below is example auxiliary function and main function, usually students
// don't need to modify ---
// --- 以下是輔助函數和主函數範例 ---

// Provide a simple implementation of find_min_small for compilation and testing
// 為了讓程式可以編譯和測試，我們提供一個 find_min_small 的簡單實現
int find_min_small(const std::vector<int> &arr, int low, int high) {
  if (low > high) {
    // Return a very large value or handle error appropriately
    // 返回一個極大值或進行適當的錯誤處理
    return std::numeric_limits<int>::max();
  }
  int min_val = arr[low];
  // Iterate from the second element up to high
  // 從第二個元素迭代到 high
  for (int i = low + 1; i <= high; ++i) {
    if (arr[i] < min_val) {
      min_val = arr[i];
    }
  }
  return min_val;
}

// Example main function (for reading input and calling the student's function)
// 主函數範例 (用於讀取輸入和呼叫學生的函數)
#include <iostream>

int main() {
  // Read array size N
  // 讀取陣列大小 N
  int n;

  // Read array elements
  // 讀取陣列元素
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  // Assume we want to query the minimum of the entire array
  // 假設我們要查詢整個陣列的最小值
  int low_query = 0;
  int high_query = n - 1;

  // Call the student's implemented divide and conquer function
  // 呼叫學生實作的分治函數
  if (n > 0) {
    int overall_min = find_min_dc(arr, low_query, high_query);
    // (中) 陣列中的最小值是：
    std::cout << overall_min << std::endl;
  } else {
    // (中) 陣列是空的。
    std::cout << std::endl;
  }

  return 0;
}
