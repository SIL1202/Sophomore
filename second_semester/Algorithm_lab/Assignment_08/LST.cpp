#include <algorithm> // For std::max_element and std::max
#include <iostream>
#include <vector>
using namespace std;

int longest_increasing_subsequence(const std::vector<int> &nums) {
  if (nums.empty()) {
    return 0;
  }
  int n = nums.size();
  std::vector<int> dp(n, 1);
  // Initialize dp[i] = 1 for all i // 初始化所有 dp[i] = 1

  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[j] < nums[i]) {
        dp[i] = std::max(dp[i], dp[j] + 1);
      }
    }
  }

  // The LIS length is the maximum value in the dp array
  // LIS 長度是 dp 陣列中的最大值
  int max_len = 0;
  if (n > 0) { // Ensure dp is not empty before accessing
    max_len = dp[0];
    for (int i = 1; i < n; ++i) {
      if (dp[i] > max_len) {
        max_len = dp[i];
      }
    }
  }
  // Or simply: if (n > 0) max_len = *std::max_element(dp.begin(), dp.end());
  // else max_len = 0;
  return max_len;
}

int main() { // Renamed to avoid conflict
  cout << "\n--- Longest Increasing Subsequence ---" << endl;

  vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
  cout << "LIS length for {10, 9, 2, 5, 3, 7, 101, 18}: "
       << longest_increasing_subsequence(nums1) << endl; // Expected: 4

  vector<int> nums2 = {0, 1, 0, 3, 2, 3};
  cout << "LIS length for {0, 1, 0, 3, 2, 3}: "
       << longest_increasing_subsequence(nums2) << endl; // Expected: 4

  vector<int> nums3 = {7, 7, 7, 7, 7};
  cout << "LIS length for {7, 7, 7, 7, 7}: "
       << longest_increasing_subsequence(nums3) << endl; // Expected: 1

  vector<int> nums4 = {3, 10, 2, 1, 20};
  cout << "LIS length for {3, 10, 2, 1, 20}: "
       << longest_increasing_subsequence(nums4) << endl; // Expected: 3

  vector<int> nums5 = {};
  cout << "LIS length for {}: " << longest_increasing_subsequence(nums5)
       << endl; // Expected: 0
  return 0;
}
