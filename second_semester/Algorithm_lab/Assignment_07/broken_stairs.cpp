#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
#define tp top_down
#define bu bottom_up

unordered_set<int> broken;

int tp(int n) {
  static vector<int> dp = {-1};
  if (n < 0)
    return 0;
  if (broken.count(n))
    return 0;
  if (n == 0)
    return 1;
  if (n >= dp.size())
    dp.resize(n + 1, -1);
  if (dp[n] != -1)
    return dp[n];

  return dp[n] = tp(n - 1) + tp(n - 2);
}

int bu(int n) {
  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    if (broken.count(i))
      continue;
    if (i >= 1)
      dp[i] += dp[i - 1];
    if (i >= 2)
      dp[i] += dp[i - 2];
  }
  return dp[n];
}

int main() {
  int n;
  cin >> n;

  broken = {3, 5};

  cout << tp(n);
  cout << '\n';
  cout << bu(n);
  return 0;
}
