#include "tsp_solver.h"

// Constructor: initialize number of cities and distance matrix
TSP::TSP(int n, const vector<vector<int>> &dist) : n(n), dist(dist) {}

// Solve TSP using DFS (Backtracking)
int TSP::solveDFS() {
  bestCost = INT_MAX;       // Initialize best cost to a very large number
  visitCount = 0;           // Reset visit count
  visited.assign(n, false); // Reset visited cities
  visited[0] = true;        // Start from city 0
  dfs(0, 1, 0);             // Begin DFS from city 0, visited 1 city, cost 0
  return bestCost;          // Return the minimum cost found
}

// Solve TSP using BFS (Breadth-First Search)
int TSP::solveBFS() {
  struct Node {
    int city;             // Current city
    int count;            // Number of cities visited so far
    int cost;             // Total cost so far
    vector<bool> visited; // Visited state of all cities
  };

  queue<Node> q;
  bestCost = INT_MAX;
  visitCount = 0;

  vector<bool> initialVisited(n, false);
  initialVisited[0] = true; // Start from city 0

  q.push({0, 1, 0, initialVisited}); // Push initial state into queue

  while (!q.empty()) {
    Node node = q.front();
    q.pop();
    visitCount++;

    // If all cities are visited and there is a return path to the start
    if (node.count == n && dist[node.city][0] > 0) {
      bestCost = min(bestCost, node.cost + dist[node.city][0]);
      continue;
    }

    // Explore all possible next cities
    for (int next = 0; next < n; ++next) {
      if (!node.visited[next] && dist[node.city][next] > 0) {
        Node nextNode = node;
        nextNode.city = next;
        nextNode.count++;
        nextNode.cost += dist[node.city][next];
        nextNode.visited[next] = true;
        q.push(nextNode); // Push new path into queue
      }
    }
  }

  return bestCost; // Return the best path cost found
}

// Solve TSP using Best-First Search with lower bound estimation (Branch and
// Bound)
int TSP::solveBestFS() {
  struct Node {
    int city;
    int count;
    int cost;
    vector<bool> visited;
    int priority; // Total estimated cost = actual cost + heuristic (lower
                  // bound)

    // Define comparison for min-heap (smaller priority has higher priority)
    bool operator<(const Node &other) const {
      return priority > other.priority;
    }
  };

  priority_queue<Node> pq;
  bestCost = INT_MAX;
  visitCount = 0;

  vector<bool> initialVisited(n, false);
  initialVisited[0] = true;

  int lower = getLowerBound(initialVisited, 0); // Initial lower bound estimate
  /*
  // int lower = getMSTLowerBound(dist, visited);
     priority = cost_so_far + lower;
  */
  pq.push({0, 1, 0, initialVisited, 0 + lower}); // Start from city 0

  while (!pq.empty()) {
    Node node = pq.top();
    pq.pop();
    visitCount++;

    // Found complete tour and can return to start
    if (node.count == n && dist[node.city][0] > 0) {
      bestCost = min(bestCost, node.cost + dist[node.city][0]);
      continue;
    }

    // Try all next unvisited cities
    for (int next = 0; next < n; ++next) {
      if (!node.visited[next] && dist[node.city][next] > 0) {
        Node nextNode = node;
        nextNode.city = next;
        nextNode.count++;
        nextNode.cost += dist[node.city][next];
        nextNode.visited[next] = true;

        int est = getLowerBound(nextNode.visited, next); // Heuristic
        nextNode.priority = nextNode.cost + est;

        // Branch and Bound: prune paths that already exceed bestCost
        if (nextNode.priority < bestCost) {
          pq.push(nextNode);
        }
      }
    }
  }

  return bestCost;
}

// Return how many times DFS/BFS/BestFS was called (for performance analysis)
int TSP::getVisitCount() const { return visitCount; }

// DFS helper function (recursive backtracking)
void TSP::dfs(int city, int count, int cost) {
  visitCount++;

  // If all cities visited and can return to the start
  if (count == n && dist[city][0] > 0) {
    bestCost = min(bestCost, cost + dist[city][0]); // Update best cost
    return;
  }

  // Explore next possible cities
  for (int next = 0; next < n; ++next) {
    if (!visited[next] && dist[city][next] > 0) {
      visited[next] = true;                          // Mark as visited
      dfs(next, count + 1, cost + dist[city][next]); // Recurse
      visited[next] = false;                         // Backtrack
    }
  }
}

// Estimate a lower bound for remaining path from current city
int TSP::getLowerBound(const vector<bool> &visited, int city) const {
  int minEdge = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (!visited[i] && dist[city][i] > 0) {
      minEdge = min(minEdge,
                    dist[city][i]); // Choose minimum cost to an unvisited city
    }
  }
  return (minEdge == INT_MAX ? 0 : minEdge); // Return 0 if no edge found
}

// Estimate a lower bound for the TSP using Minimum Spanning Tree (MST)
// This function computes the MST cost over the unvisited cities using Prim's
// algorithm
int getMSTLowerBound(const vector<vector<int>> &dist,
                     const vector<bool> &visited) {
  int n = dist.size();          // Number of cities
  vector<bool> inMST(n, false); // Track which nodes are already in the MST
  vector<int> minEdge(
      n, INT_MAX); // Minimum edge weight to connect a node to the MST
  int total = 0;   // Total cost of MST

  // Start MST from the first unvisited city
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      minEdge[i] = 0;
      break;
    }
  }

  // Build MST using Prim's algorithm
  for (int i = 0; i < n; ++i) {
    int u = -1;

    // Find the unvisited node with the smallest edge to the MST
    for (int v = 0; v < n; ++v)
      if (!visited[v] && !inMST[v] && (u == -1 || minEdge[v] < minEdge[u]))
        u = v;

    if (u == -1)
      break;             // All reachable unvisited nodes are added
    inMST[u] = true;     // Add node u to MST
    total += minEdge[u]; // Add its edge cost

    // Update minEdge for remaining unvisited nodes
    for (int v = 0; v < n; ++v)
      if (!visited[v] && !inMST[v] && dist[u][v] < minEdge[v])
        minEdge[v] = dist[u][v];
  }

  return total; // Return the MST cost (lower bound)
}
