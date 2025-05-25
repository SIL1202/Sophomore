#include "tsp_solver.h"

TSP::TSP(int n, const vector<vector<int>> &dist) : n(n), dist(dist) {}

// Solve TSP using DFS (Backtracking)
int TSP::solveDFS() {
  bestCost = INT_MAX;
  visitCount = 0;
  visited.assign(n, false);
  visited[0] = true; // Start from city 0
  dfs(0, 1, 0);
  return bestCost;
}

// Solve TSP using BFS (Breadth-First Search)
int TSP::solveBFS() {
  struct Node {
    int city;
    int count;
    int cost;
    vector<bool> visited;
  };

  queue<Node> q;
  bestCost = INT_MAX;
  visitCount = 0;

  vector<bool> initialVisited(n, false);
  initialVisited[0] = true;

  q.push({0, 1, 0, initialVisited});

  while (!q.empty()) {
    Node node = q.front();
    q.pop();
    visitCount++;

    // Check if all cities visited and a return path exists
    if (node.count == n && dist[node.city][0] > 0) {
      bestCost = min(bestCost, node.cost + dist[node.city][0]);
      continue;
    }

    // Try visiting each unvisited city
    for (int next = 0; next < n; ++next) {
      if (!node.visited[next] && dist[node.city][next] > 0) {
        Node nextNode = node;
        nextNode.city = next;
        nextNode.count++;
        nextNode.cost += dist[node.city][next];
        nextNode.visited[next] = true;
        q.push(nextNode);
      }
    }
  }

  return bestCost;
}

// Solve TSP using Best-First Search with a lower bound estimation
int TSP::solveBestFS() {
  struct Node {
    int city;
    int count;
    int cost;
    vector<bool> visited;
    int priority; // cost + estimated lower bound

    // Min-heap: lower priority value gets higher precedence
    bool operator<(const Node &other) const {
      return priority > other.priority;
    }
  };

  priority_queue<Node> pq;
  bestCost = INT_MAX;
  visitCount = 0;

  vector<bool> initialVisited(n, false);
  initialVisited[0] = true;

  int lower = getLowerBound(initialVisited, 0);
  pq.push({0, 1, 0, initialVisited, 0 + lower});

  while (!pq.empty()) {
    Node node = pq.top();
    pq.pop();
    visitCount++;

    if (node.count == n && dist[node.city][0] > 0) {
      bestCost = min(bestCost, node.cost + dist[node.city][0]);
      continue;
    }

    for (int next = 0; next < n; ++next) {
      if (!node.visited[next] && dist[node.city][next] > 0) {
        Node nextNode = node;
        nextNode.city = next;
        nextNode.count++;
        nextNode.cost += dist[node.city][next];
        nextNode.visited[next] = true;

        int est = getLowerBound(nextNode.visited, next);
        nextNode.priority = nextNode.cost + est;

        if (nextNode.priority < bestCost) { // Branch-and-bound condition
          pq.push(nextNode);
        }
      }
    }
  }
  return bestCost;
}

int TSP::getVisitCount() const { return visitCount; }

// DFS helper function
void TSP::dfs(int city, int count, int cost) {
  visitCount++;

  if (count == n && dist[city][0] > 0) {
    bestCost = min(bestCost, cost + dist[city][0]);
    return;
  }

  for (int next = 0; next < n; ++next) {
    if (!visited[next] && dist[city][next] > 0) {
      visited[next] = true;
      dfs(next, count + 1, cost + dist[city][next]);
      visited[next] = false;
    }
  }
}

// Estimate lower bound from current city to remaining unvisited cities
int TSP::getLowerBound(const vector<bool> &visited, int city) const {
  int minEdge = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (!visited[i] && dist[city][i] > 0)
      minEdge = min(minEdge, dist[city][i]);
  }
  return (minEdge == INT_MAX ? 0 : minEdge);
}
