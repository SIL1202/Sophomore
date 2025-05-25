#include "tsp_fast_algorithms.h"

// Nearest Neighbor Heuristic (Greedy Approach)
// Constructs a tour by always visiting the closest unvisited city next.
// Starts from city 0 and returns a complete tour path along with its cost.
std::vector<int> tspNearestNeighbor(const std::vector<std::vector<int>> &dist,
                                    int &cost) {
  int n = dist.size();                 // Total number of cities
  std::vector<bool> visited(n, false); // Tracks whether a city has been visited
  std::vector<int> path;               // Stores the final tour path
  cost = 0;                            // Total tour cost accumulator

  int current = 0; // Start from city 0
  visited[current] = true;
  path.push_back(current);

  // Repeat until all cities are visited
  for (int step = 1; step < n; ++step) {
    int nextCity = -1;
    int minDist = std::numeric_limits<int>::max();

    // Find the nearest unvisited city
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && dist[current][i] > 0 && dist[current][i] < minDist) {
        minDist = dist[current][i];
        nextCity = i;
      }
    }

    // Move to the next city
    if (nextCity != -1) {
      visited[nextCity] = true;
      path.push_back(nextCity);
      cost += dist[current][nextCity];
      current = nextCity;
    }
  }

  // Return to starting point to complete the cycle
  cost += dist[current][path[0]];
  path.push_back(path[0]); // Make the tour complete by returning to the start

  return path; // Return the full tour path
}

// Held-Karp Algorithm (Dynamic Programming Exact Solution)
// Time complexity: O(n^2 * 2^n)
// dp[mask][u] = minimum cost to reach subset `mask` ending at city `u`
int tspHeldKarp(const vector<vector<int>> &dist) {
  int n = dist.size();
  int N = 1 << n; // Total number of subsets
  vector<vector<int>> dp(N, vector<int>(n, INT_MAX));
  dp[1][0] = 0; // Start from city 0, only city 0 is visited

  // Iterate through all subsets of cities
  for (int mask = 1; mask < N; ++mask) {
    for (int u = 0; u < n; ++u) {
      if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX)
        continue;
      // Try visiting a new city v
      for (int v = 0; v < n; ++v) {
        if (mask & (1 << v) || dist[u][v] == 0)
          continue;
        int nextMask = mask | (1 << v);
        dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + dist[u][v]);
      }
    }
  }

  // Final step: return to city 0 and complete the tour
  int minCost = INT_MAX;
  for (int u = 1; u < n; ++u) {
    if (dist[u][0] > 0 && dp[N - 1][u] != INT_MAX)
      minCost = min(minCost, dp[N - 1][u] + dist[u][0]);
  }
  return minCost;
}
