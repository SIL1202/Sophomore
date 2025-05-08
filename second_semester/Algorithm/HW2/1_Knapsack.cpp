#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
using namespace chrono;

/*
 * ---------- 0/1 Knapsack – Bottom-Up DP ----------
 *
 * dp[i][j] = best profit when only first i items are available
 *            and remaining capacity is j.
 *
 * Time  : O(n W)
 * Space : O(n W)   (could be reduced to O(W) with a rolling array)
 */
int Bottom_up(vector<int> &p, vector<int> &w, int total) {
  int n = p.size();
  vector<vector<int>> dp(n + 1, vector<int>(total + 1, 0)); // init = 0

  for (int i = 1; i <= n; ++i) {       // items
    for (int j = 1; j <= total; ++j) { // capacity
      if (w[i - 1] <= j) {
        // Option 1: take item i-1
        int take = p[i - 1] + dp[i - 1][j - w[i - 1]];
        // Option 2: skip item i-1
        int skip = dp[i - 1][j];
        dp[i][j] = max(take, skip);
      } else {
        // Item too heavy → cannot take
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[n][total]; // optimal profit
}

/*
 * ---------- Top-Down DP (memoised recursion) ----------
 *
 * Same recurrence as Bottom-Up, but computed lazily.
 * cache[n][c] stores best profit using items 0…n with capacity c.
 */
vector<vector<int>> cache;

int recursive(vector<int> &p, vector<int> &w, int capacity, int idx) {
  if (idx < 0)
    return 0; // no items left
  if (cache[idx][capacity] != -1)
    return cache[idx][capacity];

  // Option 1: skip current item
  int best = recursive(p, w, capacity, idx - 1);

  // Option 2: take current item if it fits
  if (w[idx] <= capacity) {
    int take = p[idx] + recursive(p, w, capacity - w[idx], idx - 1);
    best = max(best, take);
  }

  return cache[idx][capacity] = best;
}

int Top_Down(vector<int> &p, vector<int> &w, int capacity) {
  cache.assign(p.size(), vector<int>(capacity + 1, -1));
  return recursive(p, w, capacity, static_cast<int>(p.size()) - 1);
}

/*
 * ---------- Greedy Heuristic ----------
 *
 * Sort items by value/weight ratio (descending) and pack while possible.
 * Works optimally only for the fractional knapsack; here it is an
 * approximation.
 *
 * Time : O(n log n) due to sorting
 * Space: O(n) for ratio list
 */
int Greedy(vector<int> &p, vector<int> &w, int capacity) {
  vector<pair<double, int>> ratioIndex; // {ratio, item-index}
  for (int i = 0; i < p.size(); ++i)
    ratioIndex.push_back({static_cast<double>(p[i]) / w[i], i});

  sort(ratioIndex.rbegin(), ratioIndex.rend()); // highest ratio first

  int totalProfit = 0;
  for (auto [ratio, idx] : ratioIndex) {
    if (w[idx] <= capacity) {
      capacity -= w[idx];
      totalProfit += p[idx];
    }
  }
  return totalProfit;
}

/* -------- Test-case loader ----------
 * Expected file format (lines beginning with # are ignored):
 *   n  W
 *   p1 p2 ... pn
 *   w1 w2 ... wn
 * (repeated for each test case)
 */
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
    stringstream header(line);
    header >> tc.n >> tc.totalWeight;

    // profits line
    getline(in, line);
    stringstream ps(line);
    tc.profits.resize(tc.n);
    for (int i = 0; i < tc.n; ++i)
      ps >> tc.profits[i];

    // weights line
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

    /* ---- Bottom-Up ---- */
    auto t0 = high_resolution_clock::now();
    int ansB = Bottom_up(tc.profits, tc.weights, tc.totalWeight);
    auto t1 = high_resolution_clock::now();
    auto timeB = duration_cast<microseconds>(t1 - t0).count();

    /* ---- Top-Down ---- */
    t0 = high_resolution_clock::now();
    int ansT = Top_Down(tc.profits, tc.weights, tc.totalWeight);
    t1 = high_resolution_clock::now();
    auto timeT = duration_cast<microseconds>(t1 - t0).count();

    /* ---- Greedy ---- */
    t0 = high_resolution_clock::now();
    int ansG = Greedy(tc.profits, tc.weights, tc.totalWeight);
    t1 = high_resolution_clock::now();
    auto timeG = duration_cast<microseconds>(t1 - t0).count();

    /* ---- Output ---- */
    cout << "[" << i << "] Bottom-Up  profit: " << ansB << "\n";
    cout << "[" << i << "] Bottom-Up  time (µs): " << timeB << "\n";
    cout << "[" << i << "] Top-Down   profit: " << ansT << "\n";
    cout << "[" << i << "] Top-Down   time (µs): " << timeT << "\n";
    cout << "[" << i << "] Greedy     profit: " << ansG << "\n";
    cout << "[" << i << "] Greedy     time (µs): " << timeG << "\n";
    cout << "----------------------------------------\n";
  }
}
