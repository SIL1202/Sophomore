// TSP experiment runner: auto-generate symmetric distance matrices and test TSP
// algorithms
#include "tsp_fast_algorithms.h" // Nearest Neighbor + Held-Karp
#include "tsp_metaheuristics.h"
#include "tsp_solver.h" // Your main TSP class (DFS/BFS/BestFS)
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Generate a symmetric distance matrix with weights in [minW, maxW]
vector<vector<int>> generateSymmetricMatrix(int n, int minW, int maxW) {
  vector<vector<int>> dist(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int w = rand() % (maxW - minW + 1) + minW;
      dist[i][j] = dist[j][i] = w;
    }
    dist[i][i] = 0;
  }
  return dist;
}

void runExperiment(int n, int minW, int maxW) {
  auto dist = generateSymmetricMatrix(n, minW, maxW);
  TSP tsp(n, dist);

  int costDFS = tsp.solveDFS();
  int dfsVisits = tsp.getVisitCount();

  int costBFS = tsp.solveBFS();
  int bfsVisits = tsp.getVisitCount();

  int costBest = tsp.solveBestFS();
  int bestVisits = tsp.getVisitCount();

  int nnCost;
  std::vector<int> nnPath = tspNearestNeighbor(dist, nnCost); // FIXED
  int costDP = (n <= 20 ? tspHeldKarp(dist) : -1);

  int cost2opt = tsp2opt(nnPath, dist); // Use NN result
  int costSA = tspSimulatedAnnealing(dist);
  int costGA = tspGenetic(dist);

  cout << "Cities: " << n << ", Range: [" << minW << ", " << maxW << "]\n";
  cout << "  DFS:       cost = " << setw(3) << costDFS
       << ", visits = " << dfsVisits << '\n';
  cout << "  BFS:       cost = " << setw(3) << costBFS
       << ", visits = " << bfsVisits << '\n';
  cout << "  BestFS:    cost = " << setw(3) << costBest
       << ", visits = " << bestVisits << '\n';
  cout << "  NN:        cost = " << setw(3) << nnCost
       << " (greedy heuristic)\n";

  if (costDP != -1)
    cout << "  Held-Karp: cost = " << setw(3) << costDP << " (exact DP)\n";
  cout << "  2-opt:     cost = " << setw(3) << cost2opt
       << " (optimized path)\n";
  cout << "  SA:        cost = " << setw(3) << costSA
       << " (simulated annealing)\n";
  cout << "  GA:        cost = " << setw(3) << costGA
       << " (genetic algorithm)\n\n";
}

int main() {
  srand(time(nullptr));

  vector<int> cityCounts = {4, 6, 8, 10};
  vector<pair<int, int>> ranges = {{1, 10}, {1, 100}};

  for (int n : cityCounts) {
    for (auto [minW, maxW] : ranges) {
      runExperiment(n, minW, maxW);
    }
  }

  return 0;
}
