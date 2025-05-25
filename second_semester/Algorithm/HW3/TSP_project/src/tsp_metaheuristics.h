// tsp_metaheuristics.h
// Contains TSP solvers based on metaheuristics:
// - 2-opt optimization
// - Simulated Annealing (SA)
// - Genetic Algorithm (GA, simplified)

#ifndef TSP_METAHEURISTICS_H
#define TSP_METAHEURISTICS_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

// Calculate total cost of a TSP path
int calcPathCost(const vector<int> &path, const vector<vector<int>> &dist);

// 2-opt optimization (starting from initial path)
int tsp2opt(vector<int> path, const vector<vector<int>> &dist);

// Simulated Annealing
int tspSimulatedAnnealing(const vector<vector<int>> &dist, int maxIter = 10000);

// Simplified Genetic Algorithm
int tspGenetic(const vector<vector<int>> &dist, int populationSize = 50,
               int generations = 300);

#endif // TSP_METAHEURISTICS_H
