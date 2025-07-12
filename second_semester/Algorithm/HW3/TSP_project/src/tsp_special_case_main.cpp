// tsp_special_case_main.cpp
// Run multiple TSP algorithms on 2D special case data

#include "tsp_fast_algorithms.h"
#include "tsp_metaheuristics.h"
#include "tsp_solver.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct Point {
  double x, y;
};

double dist(const Point &a, const Point &b) {
  return hypot(a.x - b.x, a.y - b.y);
}

vector<Point> generateRandomCities(int n, double minCoord = 0,
                                   double maxCoord = 100) {
  vector<Point> cities;
  mt19937 rng(time(nullptr));
  uniform_real_distribution<double> uni(minCoord, maxCoord);
  for (int i = 0; i < n; ++i) {
    cities.push_back({uni(rng), uni(rng)});
  }
  return cities;
}

vector<vector<int>> buildDistanceMatrix(const vector<Point> &cities) {
  int n = cities.size();
  vector<vector<int>> dmat(n, vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      dmat[i][j] = static_cast<int>(round(dist(cities[i], cities[j])));
  return dmat;
}

void runExperiment(int n, int repeat = 1) {
  cout << "Cities: " << n << ", Dimension: 2D plane\n";

  for (int r = 1; r <= repeat; ++r) {
    cout << "  [Round " << r << "]\n";

    vector<Point> cities = generateRandomCities(n);
    auto dist = buildDistanceMatrix(cities);
    TSP tsp(n, dist);

    int costDFS = tsp.solveDFS();
    int dfsVisits = tsp.getVisitCount();

    int costBFS = tsp.solveBFS();
    int bfsVisits = tsp.getVisitCount();

    int costBest = tsp.solveBestFS();
    int bestVisits = tsp.getVisitCount();

    int nnCost;
    vector<int> nnPath = tspNearestNeighbor(dist, nnCost);
    int costDP = (n <= 20 ? tspHeldKarp(dist) : -1);
    int cost2opt = tsp2opt(nnPath, dist);
    int costSA = tspSimulatedAnnealing(dist);
    int costGA = tspGenetic(dist);

    cout << "    DFS:    " << costDFS << " | visits = " << dfsVisits << "\n";
    cout << "    BFS:    " << costBFS << " | visits = " << bfsVisits << "\n";
    cout << "    BestFS: " << costBest << " | visits = " << bestVisits << "\n";
    cout << "    NN:     " << nnCost << "\n";
    cout << "    2-opt:  " << cost2opt << "\n";
    cout << "    SA:     " << costSA << "\n";
    cout << "    GA:     " << costGA << "\n";
    if (costDP != -1)
      cout << "    Held-Karp: " << costDP << "\n";
  }

  cout << "------------------------------------\n\n";
}

int main() {
  vector<int> cityCounts = {4, 6, 8, 10};
  for (int n : cityCounts) {
    runExperiment(n, 5); // repeat 5 times for each size
  }
  return 0;
}
