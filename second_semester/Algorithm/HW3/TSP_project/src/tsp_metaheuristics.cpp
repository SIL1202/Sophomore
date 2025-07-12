#include "tsp_metaheuristics.h"

// Calculate the total cost of a TSP tour path
int calcPathCost(const vector<int> &path, const vector<vector<int>> &dist) {
  int cost = 0, n = path.size();
  for (int i = 0; i < n; ++i)
    cost += dist[path[i]][path[(i + 1) % n]]; // wrap around to form a cycle
  return cost;
}

// 2-opt optimization: improves the initial path by reversing two edges at a
// time
int tsp2opt(vector<int> path, const vector<vector<int>> &dist) {
  int n = path.size();
  bool improved = true;
  while (improved) {
    improved = false;
    for (int i = 1; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (j - i == 1)
          continue; // Skip adjacent nodes (no effect)
        vector<int> newPath = path;
        reverse(newPath.begin() + i, newPath.begin() + j); // reverse segment
        if (calcPathCost(newPath, dist) < calcPathCost(path, dist)) {
          path = newPath;
          improved = true; // Repeat if improvement found
        }
      }
    }
  }
  return calcPathCost(path, dist);
}

// Simulated Annealing: probabilistically explores worse paths to escape local
// optima
int tspSimulatedAnnealing(const vector<vector<int>> &dist, int maxIter) {
  int n = dist.size();
  vector<int> path(n);
  iota(path.begin(), path.end(), 0); // Initial path: 0 -> 1 -> 2 -> ... -> n-1
  int bestCost = calcPathCost(path, dist);
  vector<int> bestPath = path;

  double T = 1000.0, alpha = 0.995; // Initial temperature and cooling rate
  mt19937 rng(time(nullptr));
  uniform_int_distribution<int> randCity(1, n - 1);   // Avoid city 0
  uniform_real_distribution<double> rand01(0.0, 1.0); // Random in [0, 1]

  for (int iter = 0; iter < maxIter; ++iter) {
    int i = randCity(rng), j = randCity(rng);
    if (i == j)
      continue;
    if (i > j)
      swap(i, j);
    vector<int> newPath = path;
    reverse(newPath.begin() + i, newPath.begin() + j);
    int newCost = calcPathCost(newPath, dist);
    int delta = newCost - bestCost;

    // Accept better solution or probabilistically accept worse one
    if (delta < 0 || rand01(rng) < exp(-delta / T)) {
      path = newPath;
      if (newCost < bestCost) {
        bestCost = newCost;
        bestPath = newPath;
      }
    }
    T *= alpha; // Gradually cool down
  }
  return bestCost;
}

// Genetic Algorithm: evolves a population of paths using crossover and mutation
int tspGenetic(const vector<vector<int>> &dist, int populationSize,
               int generations) {
  int n = dist.size();
  mt19937 rng(time(nullptr));
  vector<vector<int>> population;

  // Create initial random population
  for (int i = 0; i < populationSize; ++i) {
    vector<int> path(n);
    iota(path.begin(), path.end(), 0);
    shuffle(path.begin() + 1, path.end(), rng); // Fix city 0 at start
    population.push_back(path);
  }

  for (int gen = 0; gen < generations; ++gen) {
    // Sort by fitness (total tour cost)
    sort(population.begin(), population.end(),
         [&](const auto &a, const auto &b) {
           return calcPathCost(a, dist) < calcPathCost(b, dist);
         });

    // Elitism: keep top 10 paths
    vector<vector<int>> nextGen(population.begin(), population.begin() + 10);
    uniform_int_distribution<int> parentPick(0, 9);

    // Generate offspring until population is full
    while (nextGen.size() < populationSize) {
      vector<int> p1 = population[parentPick(rng)];
      vector<int> p2 = population[parentPick(rng)];

      // Order Crossover (OX)
      int a = rng() % n, b = rng() % n;
      if (a > b)
        swap(a, b);
      vector<int> child(n, -1);
      for (int i = a; i <= b; ++i)
        child[i] = p1[i];

      int idx = (b + 1) % n;
      for (int i = 0; i < n; ++i) {
        int city = p2[(b + 1 + i) % n];
        if (find(child.begin(), child.end(), city) == child.end()) {
          child[idx] = city;
          idx = (idx + 1) % n;
        }
      }

      // Mutation: randomly swap two cities (excluding city 0)
      if (rng() % 5 == 0) {
        int x = 1 + rng() % (n - 1), y = 1 + rng() % (n - 1);
        swap(child[x], child[y]);
      }

      nextGen.push_back(child);
    }

    population = nextGen; // Replace with next generation
  }

  return calcPathCost(population[0], dist); // Return best found solution
}
