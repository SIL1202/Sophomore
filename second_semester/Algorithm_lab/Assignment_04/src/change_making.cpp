#include <algorithm>
#include <iostream>
#include <vector>
typedef std::vector<int> IntList;

// DP
IntList change_making_dp(const IntList &C, int m) {
  std::vector<int> dp(m + 1, INT_MAX);   // dp[i] = 最少幾枚湊出 i
  std::vector<int> last_coin(m + 1, -1); // 記錄每個 dp[i] 是由哪個硬幣湊出

  dp[0] = 0; // 湊出 0 元，不需要硬幣

  for (int coin : C) {
    for (int i = coin; i <= m; ++i) {
      if (dp[i - coin] != INT_MAX && dp[i - coin] + 1 < dp[i]) {
        dp[i] = dp[i - coin] + 1;
        last_coin[i] = coin;
      }
    }
  }

  if (dp[m] == INT_MAX)
    return {}; // 無法湊出 m 元

  // 回溯出硬幣組合
  IntList A(C.size(), 0);
  for (int i = m; i > 0; i -= last_coin[i]) {
    int coin = last_coin[i];
    int idx = std::find(C.begin(), C.end(), coin) - C.begin();
    ++A[idx];
  }

  return A;
}

int main() {
  IntList C = {1, 3, 4};
  int m = 6;

  IntList ans = change_making_dp(C, m);
  if (ans.empty()) {
    std::cout << "No solution\n";
  } else {
    for (int count : ans)
      std::cout << count << " ";
    std::cout << "\n";
  }
}

// C = {1, 5, 10}
// m = 18
// Greedy method
/* typedef std::vector<int> IntList;

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
} */
