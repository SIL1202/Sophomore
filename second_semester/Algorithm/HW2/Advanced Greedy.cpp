#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using namespace chrono;

// Bottom-Up Dynamic Programming
int Bottom_up(vector<int> &p, vector<int> &w, int total) {
  int n = p.size();
  vector<vector<int>> dp(n + 1, vector<int>(total + 1));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= total; j++) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (w[i - 1] <= j)
        dp[i][j] = max(p[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[n][total];
}

// Traditional Greedy: profit / weight
int Greedy_ratio(const vector<int> &p, const vector<int> &w, int total) {
  int n = p.size();
  vector<pair<double, int>> items;
  for (int i = 0; i < n; i++)
    items.push_back({(double)p[i] / w[i], i});
  sort(items.rbegin(), items.rend());
  int profit = 0;
  for (auto [_, i] : items) {
    if (w[i] <= total) {
      total -= w[i];
      profit += p[i];
    }
  }
  return profit;
}

// Greedy with profit / sqrt(weight)
int Greedy_sqrt(const vector<int> &p, const vector<int> &w, int total) {
  int n = p.size();
  vector<pair<double, int>> items;
  for (int i = 0; i < n; i++)
    items.push_back({(double)p[i] / sqrt(w[i]), i});
  sort(items.rbegin(), items.rend());
  int profit = 0;
  for (auto [_, i] : items) {
    if (w[i] <= total) {
      total -= w[i];
      profit += p[i];
    }
  }
  return profit;
}

// Greedy with penalized ratio: profit / (weight + penalty)
int Greedy_penalty(const vector<int> &p, const vector<int> &w, int total,
                   double penalty = 5.0) {
  int n = p.size();
  vector<pair<double, int>> items;
  for (int i = 0; i < n; i++)
    items.push_back({(double)p[i] / (w[i] + penalty), i});
  sort(items.rbegin(), items.rend());
  int profit = 0;
  for (auto [_, i] : items) {
    if (w[i] <= total) {
      total -= w[i];
      profit += p[i];
    }
  }
  return profit;
}

// Greedy + brute force on top-k candidates
int Greedy_k_best(const vector<int> &p, const vector<int> &w, int total,
                  int k = 10) {
  int n = p.size();
  vector<pair<double, int>> items;
  for (int i = 0; i < n; i++)
    items.push_back({(double)p[i] / w[i], i});
  sort(items.rbegin(), items.rend());
  k = min(k, n);
  int best = 0;
  for (int subset = 0; subset < (1 << k); subset++) {
    int sum_w = 0, sum_p = 0;
    for (int j = 0; j < k; j++) {
      if (subset & (1 << j)) {
        sum_w += w[items[j].second];
        sum_p += p[items[j].second];
      }
    }
    if (sum_w <= total)
      best = max(best, sum_p);
  }
  return best;
}

int main() {
  // Generate large test case
  int n = 500;
  int totalWeight = 1000;
  vector<int> profits(n), weights(n);
  for (int i = 0; i < n; i++) {
    profits[i] = rand() % 1000 + 1;
    weights[i] = rand() % 100 + 1;
  }

  // Bottom-Up
  auto t1 = high_resolution_clock::now();
  int dp_result = Bottom_up(profits, weights, totalWeight);
  auto t2 = high_resolution_clock::now();
  cout << "Bottom-Up DP: " << dp_result
       << "\tTime: " << duration_cast<milliseconds>(t2 - t1).count() << " ms"
       << endl;

  // Greedy methods
  cout << "Greedy (p/w): " << Greedy_ratio(profits, weights, totalWeight)
       << endl;
  cout << "Greedy (p/sqrt(w)): " << Greedy_sqrt(profits, weights, totalWeight)
       << endl;
  cout << "Greedy (p/(w+penalty)): "
       << Greedy_penalty(profits, weights, totalWeight) << endl;
  cout << "Greedy (top-k brute force): "
       << Greedy_k_best(profits, weights, totalWeight, 12) << endl;

  return 0;
}
