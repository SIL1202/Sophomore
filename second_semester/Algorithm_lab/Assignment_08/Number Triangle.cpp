#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> grid;
vector<vector<int>> dp;

int solve(int i, int j) {
  if (i == n - 1)
    return grid[i][j];
  if (dp[i][j] != -1)
    return dp[i][j];
  dp[i][j] = grid[i][j] + max(solve(i + 1, j + 1), solve(i + 1, j));

  return dp[i][j];
}

int solve1(int i, int j) {
  if (j < 0 || j > i)
    return 0;
  if (i == 0 && j == 0)
    return grid[i][j];
  if (dp[i][j] != -1)
    return dp[i][j];

  return dp[i][j] = max(solve(i - 1, j - 1), solve(i - 1, j)) + grid[i][j];
}

int main() {
  cin >> n;
  grid.resize(n);
  dp.resize(n, vector<int>(n, -1));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i + 1; j++) {
      int x;
      cin >> x;
      grid[i].push_back(x);
    }
  }

  // 1
  // 1 2
  // 1 2 3
  // 1 2 3 4

  int Max = 0;
  // for (int j = n - 1; j >= 0; --j)
  //   Max = max(Max, solve1(n - 1, j));
  //
  Max = solve(0, 0);

  cout << Max << '\n';

  for (auto row : grid) {
    for (int col : row) {
      cout << col << ' ';
    }
    cout << '\n';
  }
  return 0;
}
