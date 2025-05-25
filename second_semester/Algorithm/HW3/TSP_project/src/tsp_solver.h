#include <queue>
#include <vector>
using namespace std;

class TSP {
public:
  TSP(int n, const vector<vector<int>> &dist);

  // Solve TSP using DFS (Backtracking)
  int solveDFS();

  // Solve TSP using BFS (Breadth-First Search)
  int solveBFS();

  // Solve TSP using Best-First Search with a lower bound estimation
  int solveBestFS();

  int getVisitCount() const;

private:
  int n;
  vector<vector<int>> dist;
  vector<bool> visited;
  int bestCost;
  int visitCount;

  // DFS helper function
  void dfs(int city, int count, int cost);

  // Estimate lower bound from current city to remaining unvisited cities
  int getLowerBound(const vector<bool> &visited, int city) const;
};
