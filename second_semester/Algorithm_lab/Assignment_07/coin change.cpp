#include <iostream>
#include <vector>
using namespace std;

int coin_change_brute(const vector<int> &coins, int x) {
  int n = coins.size();
  vector<vector<int>> dp(n, vector<int>(x + 1, 0));

  // 初始化：金額為 0 時都有一種方式（什麼都不拿）
  for (int i = 0; i < n; ++i)
    dp[i][0] = 1;

  // 處理只有第一種硬幣時的情況
  for (int j = 1; j <= x; ++j)
    dp[0][j] = (j % coins[0] == 0) ? 1 : 0;

  // 主體：對每一種硬幣、每一個金額，試試看拿幾個
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= x; ++j) {
      dp[i][j] = 0;
      for (int count = 0; count * coins[i] <= j; ++count) {
        dp[i][j] += dp[i - 1][j - count * coins[i]];
      }
    }
  }

  return dp[n - 1][x];
}

int coin_change(const std::vector<int> &coins, int x) {
  int n = coins.size();
  int dp[n][x + 1]; // declaration

  for (int i = 0; i < n; ++i)
    dp[i][0] = 1; // init

  for (int j = 1; j <= x; ++j)
    dp[0][j] = (j % coins[0] == 0) ? 1 : 0;
  // 如果金額剛好能被第一種硬幣整除，那就有一種方式。否則沒有解。

  for (int i = 1; i < n; ++i)
    for (int j = 1; j <= x; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= coins[i])
        dp[i][j] += dp[i][j - coins[i]];
    }
  return dp[n - 1][x];
}

int coin_change_1D(const std::vector<int> &coins, int amount) {
  int n = coins.size();
  std::vector<int> dp(amount + 1, 0);

  dp[0] = 1; // init
  for (int ik = 0; ik < n; ++ik)
    for (int im = coins[ik]; im <= amount; ++im)
      dp[im] += dp[im - coins[ik]];

  return dp[amount];
}

int main() {
  int n, x;
  std::cin >> n >> x;
  vector<int> a(n);
  for (int &i : a)
    std::cin >> i;

  std::cout << coin_change_brute(a, x) << '\n';
  std::cout << coin_change(a, x) << '\n';
  std::cout << coin_change_1D(a, x) << '\n';
  return 0;
}
