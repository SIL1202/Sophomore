#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int x, y;
  double g, h, f;
  shared_ptr<Node> parent;

  Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}
  bool operator>(const Node &other) const { return f > other.f; }
};

double heuristic(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

vector<shared_ptr<Node>> AStar(shared_ptr<Node> start, shared_ptr<Node> goal,
                               const vector<vector<int>> &grid) {
  auto cmp = [](const shared_ptr<Node> &a, const shared_ptr<Node> &b) {
    return a->f > b->f;
  };
  priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(cmp)>
      openSet(cmp);

  map<pair<int, int>, shared_ptr<Node>> allNodes;
  map<pair<int, int>, bool> closedSet;

  start->g = 0;
  start->h = heuristic(start->x, start->y, goal->x, goal->y);
  start->f = start->g + start->h;
  openSet.push(start);
  allNodes[{start->x, start->y}] = start;

  while (!openSet.empty()) {
    auto current = openSet.top();
    openSet.pop();

    if (current->x == goal->x && current->y == goal->y) {
      vector<shared_ptr<Node>> path;
      while (current) {
        path.push_back(current);
        current = current->parent;
      }
      reverse(path.begin(), path.end());
      return path;
    }

    closedSet[{current->x, current->y}] = true;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
      int nx = current->x + dx[i];
      int ny = current->y + dy[i];

      if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size() ||
          grid[nx][ny] == 1)
        continue;

      auto coord = make_pair(nx, ny);
      if (closedSet[coord])
        continue;

      double tentative_g = current->g + 1;

      if (allNodes.count(coord)) {
        auto neighbor = allNodes[coord];
        if (tentative_g < neighbor->g) {
          neighbor->g = tentative_g;
          neighbor->f = neighbor->g + neighbor->h;
          neighbor->parent = current;
          openSet.push(neighbor);
        }
      } else {
        auto neighbor = make_shared<Node>(nx, ny);
        neighbor->g = tentative_g;
        neighbor->h = heuristic(nx, ny, goal->x, goal->y);
        neighbor->f = neighbor->g + neighbor->h;
        neighbor->parent = current;
        allNodes[coord] = neighbor;
        openSet.push(neighbor);
      }
    }
  }

  return {};
}

int main() {
  // clang-format off
  vector<vector<int>> grid = {{0, 0, 0, 0}, 
                              {0, 1, 1, 0},
                              {0, 0, 0, 0}};
  // clang-format on

  auto start = make_shared<Node>(0, 0);
  auto goal = make_shared<Node>(2, 3);

  auto path = AStar(start, goal, grid);

  if (!path.empty()) {
    cout << "Path: ";
    for (const auto &node : path)
      cout << "(" << node->x << "," << node->y << ") ";
    cout << endl;
  } else {
    cout << "No path found." << endl;
  }

  return 0;
}
