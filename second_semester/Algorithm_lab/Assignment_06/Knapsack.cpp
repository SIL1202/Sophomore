#include <iostream>
using namespace std;

void knapsack(int n, int x, int weight[], int value[]) {
  int dp[n + 1][x + 1];

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= x; j++)
      dp[i][j] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= x; j++) {
      int pick = 0;
      if (j >= weight[i - 1]) // 注意：weight/value 是 0-based
        pick = value[i - 1] + dp[i - 1][j - weight[i - 1]];
      int skip = dp[i - 1][j];
      dp[i][j] = max(pick, skip);
    }
  }
  cout << dp[n][x];
}

int main() {
  int n, x;
  cin >> n >> x;

  int weights[n];
  int values[n];
  for (int i = 0; i < n; i++)
    cin >> weights[i];
  for (int i = 0; i < n; i++)
    cin >> values[i];

  knapsack(n, x, weights, values);
  return 0;
}
