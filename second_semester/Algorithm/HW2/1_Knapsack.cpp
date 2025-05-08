#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using namespace chrono;

int Bottom_up(vector<int> &p, vector<int> &w, int total) {
  int n = p.size();
  vector<vector<int>> dp(n + 1, vector<int>(total + 1));

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= total; j++) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (w[i - 1] <= j) {
        dp[i][j] = max(p[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
      } else
        dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[n][total];
}

vector<vector<int>> cache;
int recursive(vector<int> &p, vector<int> &w, int total, int n) {
  if (n == 0)
    return (w[n] <= total) ? p[0] : 0;

  if (cache[n][total] != -1)
    return cache[n][total];

  if (w[n] <= total)
    cache[n][total] = max(p[n] + recursive(p, w, total - w[n], n - 1),
                          recursive(p, w, total, n - 1));

  return cache[n][total];
}

int Top_Down(vector<int> &p, vector<int> &w, int total, int n) {
  return recursive(p, w, total, n - 1);
}

int Greedy(vector<int> &p, vector<int> &w, int total, int n) {
  vector<pair<double, int>> ratioIndex;
  for (int i = 0; i < n; i++)
    ratioIndex.push_back({(double)p[i] / w[i], i});

  sort(ratioIndex.rbegin(), ratioIndex.rend());

  int totalProfit = 0;
  for (auto &[ratio, idx] : ratioIndex) {
    if (w[idx] <= total) {
      totalProfit += p[idx];
      total -= w[idx];
    }
  }

  return totalProfit;
}

int main() {
  int n = 10;
  int totalWeight = 100;

  vector<int> profits{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  vector<int> weights{2, 3, 4, 5, 6, 4, 3, 7, 9, 3};

  auto start_B = chrono::high_resolution_clock::now();
  cout << "Bottom-Up total profit: " << Bottom_up(profits, weights, totalWeight)
       << endl;
  auto end_B = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<nanoseconds>(end_B - start_B);
  cout << "Bottom-Up time consumption: " << duration.count() << endl;

  auto start_T = chrono::high_resolution_clock::now();
  // for memorizing top-down approach
  cache.assign(n, vector<int>(totalWeight + 1, -1));
  cout << "Top-Down total profit: "
       << Top_Down(profits, weights, totalWeight, n) << endl;
  auto end_T = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<nanoseconds>(end_T - start_T);
  cout << "Top-Down time consumption: " << duration.count() << endl;

  auto start_G = chrono::high_resolution_clock::now();
  cout << "Greedy total profit: " << Greedy(profits, weights, totalWeight, n)
       << endl;
  auto end_G = chrono::high_resolution_clock::now();
  duration = chrono::duration_cast<nanoseconds>(end_G - start_G);
  cout << "Greedy time consumption: " << duration.count() << endl;
  return 0;
}
