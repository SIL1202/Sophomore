// tsp_fast_algorithms.h
// This file contains two faster approximate TSP algorithms:
// 1. Nearest Neighbor Heuristic
// 2. Dynamic Programming (Held-Karp) for small n <= 20

#ifndef TSP_FAST_ALGORITHMS_H
#define TSP_FAST_ALGORITHMS_H

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

// Nearest Neighbor Heuristic (Greedy)
std::vector<int> tspNearestNeighbor(const std::vector<std::vector<int>> &dist,
                                    int &cost);

// Held-Karp Dynamic Programming Algorithm
int tspHeldKarp(const vector<vector<int>> &dist);

#endif // TSP_FAST_ALGORITHMS_H
