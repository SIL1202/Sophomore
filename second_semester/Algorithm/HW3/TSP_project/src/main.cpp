// TSP experiment runner: auto-generate symmetric distance matrices and test TSP
// algorithms
#include "tsp_solver.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// (number of cities n，distance range [minW, maxW])
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

  cout << "Cities: " << n << ", Range: [" << minW << ", " << maxW << "]\n";
  cout << "  DFS:    cost = " << setw(3) << costDFS
       << ", visits = " << dfsVisits << '\n';
  cout << "  BFS:    cost = " << setw(3) << costBFS
       << ", visits = " << bfsVisits << '\n';
  cout << "  BestFS: cost = " << setw(3) << costBest
       << ", visits = " << bestVisits << "\n\n";
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
