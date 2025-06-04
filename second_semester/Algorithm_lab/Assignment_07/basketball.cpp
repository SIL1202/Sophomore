#include <iostream>
using namespace std;
#define tp top_down
#define bu bottom_up

int tp(int n) {
  static vector<int> dp(1, -1);
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  if (n >= dp.size())
    dp.resize(n + 1, -1);
  if (dp[n] != -1)
    return dp[n];

  return dp[n] = tp(n - 2) + tp(n - 3);
}

int bu(int n) {
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    if (i >= 2)
      dp[i] += dp[i - 2];
    if (i >= 3)
      dp[i] += dp[i - 3];
  }
  return dp[n];
}

int main() {
  int n;
  cin >> n;
  cout << tp(n);
  cout << '\n';
  cout << bu(n);
  return 0;
}
