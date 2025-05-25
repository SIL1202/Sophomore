#include "Tsp_fast_algorithms.h"

// Nearest Neighbor Heuristic (Greedy)
int tspNearestNeighbor(const vector<vector<int>> &dist) {
  int n = dist.size();
  vector<bool> visited(n, false);
  int cost = 0, current = 0;
  visited[0] = true;

  for (int step = 1; step < n; ++step) {
    int next = -1, minCost = INT_MAX;
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && dist[current][i] > 0 && dist[current][i] < minCost) {
        minCost = dist[current][i];
        next = i;
      }
    }
    if (next == -1)
      return INT_MAX; // invalid path
    visited[next] = true;
    cost += minCost;
    current = next;
  }

  // Return to starting city
  if (dist[current][0] > 0)
    cost += dist[current][0];
  else
    return INT_MAX;

  return cost;
}

// Held-Karp Dynamic Programming Algorithm
int tspHeldKarp(const vector<vector<int>> &dist) {
  int n = dist.size();
  int N = 1 << n;
  vector<vector<int>> dp(N, vector<int>(n, INT_MAX));
  dp[1][0] = 0; // Starting at city 0

  for (int mask = 1; mask < N; ++mask) {
    for (int u = 0; u < n; ++u) {
      if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX)
        continue;
      for (int v = 0; v < n; ++v) {
        if (mask & (1 << v) || dist[u][v] == 0)
          continue;
        int nextMask = mask | (1 << v);
        dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + dist[u][v]);
      }
    }
  }

  int minCost = INT_MAX;
  for (int u = 1; u < n; ++u) {
    if (dist[u][0] > 0 && dp[N - 1][u] != INT_MAX)
      minCost = min(minCost, dp[N - 1][u] + dist[u][0]);
  }
  return minCost;
}
