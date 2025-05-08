#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using namespace chrono;

int Bottom_up(vector<int> &p, vector<int> &w, int total);
int Top_Down(vector<int> &p, vector<int> &w, int total, int n);
int Greedy(vector<int> &p, vector<int> &w, int total, int n);

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

  int pick = 0;
  if (w[n] <= total)
    pick = p[n] + recursive(p, w, total - w[n], n - 1);

  int not_pick = recursive(p, w, total, n - 1);
  cache[n][total] = max(pick, not_pick);

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

#include <fstream>
#include <sstream>

struct TestCase {
  int n, totalWeight;
  vector<int> profits, weights;
};

vector<TestCase> loadTestCases(const string &filename) {
  ifstream in(filename);
  vector<TestCase> cases;
  string line;
  while (getline(in, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    TestCase tc;
    stringstream ss(line);
    ss >> tc.n >> tc.totalWeight;

    // 讀 profits
    getline(in, line);
    stringstream ps(line);
    tc.profits.resize(tc.n);
    for (int i = 0; i < tc.n; ++i)
      ps >> tc.profits[i];

    // 讀 weights
    getline(in, line);
    stringstream ws(line);
    tc.weights.resize(tc.n);
    for (int i = 0; i < tc.n; ++i)
      ws >> tc.weights[i];

    cases.push_back(tc);
  }
  return cases;
}

int main() {
  auto testcases = loadTestCases("input.txt");

  for (int i = 0; i < testcases.size(); ++i) {
    auto &tc = testcases[i];
    int n = tc.n;

    auto start_B = chrono::high_resolution_clock::now();
    int res_B = Bottom_up(tc.profits, tc.weights, tc.totalWeight);
    auto end_B = chrono::high_resolution_clock::now();
    auto dur_B = chrono::duration_cast<chrono::microseconds>(end_B - start_B);

    cache.assign(n, vector<int>(tc.totalWeight + 1, -1));
    auto start_T = chrono::high_resolution_clock::now();
    int res_T = Top_Down(tc.profits, tc.weights, tc.totalWeight, n);
    auto end_T = chrono::high_resolution_clock::now();
    auto dur_T = chrono::duration_cast<chrono::microseconds>(end_T - start_T);

    auto start_G = chrono::high_resolution_clock::now();
    int res_G = Greedy(tc.profits, tc.weights, tc.totalWeight, n);
    auto end_G = chrono::high_resolution_clock::now();
    auto dur_G = chrono::duration_cast<chrono::microseconds>(end_G - start_G);

    cout << "[" << i << "] Bottom-Up total profit: " << res_B << endl;
    cout << "[" << i << "] Bottom-Up time (us): " << dur_B.count() << endl;
    cout << "[" << i << "] Top-Down total profit: " << res_T << endl;
    cout << "[" << i << "] Top-Down time (us): " << dur_T.count() << endl;
    cout << "[" << i << "] Greedy total profit: " << res_G << endl;
    cout << "[" << i << "] Greedy time (us): " << dur_G.count() << endl;
  }
}
