#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
public:
  Grid()
      : state(0) // 正確的初始化無參數構造函數
  {
    for (int i = 0; i < 4; i++) {
      dir[i] = nullptr;
    }
  }

  Grid(int s)
      : state(s) // 初始化帶參構造函數
  {
    for (int i = 0; i < 4; i++) {
      dir[i] = nullptr;
    }
  }

  Grid *getDir(int d) { return dir[d]; }
  int getState() { return state; }
  void setDir(int d, Grid *g) { dir[d] = g; }
  void setState(int s) { state = s; }

private:
  Grid *dir[4];
  int state;
};

struct List {
public:
  List() { top = 0; }
  void addElement(Grid *g) {
    if (top < SIZE * SIZE) {
      data[top++] = g;
    }
  }

  Grid *removeElement() {
    if (top > 0) {
      return data[--top];
    }
    return nullptr;
  }

  void printPath() {
    int j;
    for (j = 1; j < top; j++) {
      if (data[j] == data[j - 1]->getDir(UP)) {
        cout << "UP\n";
      } else if (data[j] == data[j - 1]->getDir(DOWN)) {
        cout << "DOWN\n";
      } else if (data[j] == data[j - 1]->getDir(LEFT)) {
        cout << "LEFT\n";
      } else if (data[j] == data[j - 1]->getDir(RIGHT)) {
        cout << "RIGHT\n";
      }
    }
  }

private:
  Grid *data[SIZE * SIZE];
  int top;
};

class Maze {
public:
  Maze() { initMaze(SIZE); }

  void initMaze(int s) {
    srand(time(nullptr));

    maze = new Grid(0);
    Grid *rowStart = maze;

    // Initialize the grid and randomly assign walls
    for (int i = 0; i < s; ++i) {
      Grid *current = rowStart;
      for (int j = 1; j < s; ++j) {
        current->setDir(RIGHT, new Grid((rand() % 100) < 20 ? 1 : 0));
        current->getDir(RIGHT)->setDir(LEFT, current);
        current = current->getDir(RIGHT);
      }
      if (i < s - 1) {
        rowStart->setDir(DOWN, new Grid((rand() % 100) < 20 ? 1 : 0));
        rowStart->getDir(DOWN)->setDir(UP, rowStart);
        rowStart = rowStart->getDir(DOWN);
      }
    }

    // Ensure start and end points are 0 (empty space)
    maze->setState(0);
    Grid *end = maze;
    for (int i = 0; i < s - 1; ++i) {
      end = end->getDir(DOWN);
    }
    for (int j = 0; j < s - 1; ++j) {
      end = end->getDir(RIGHT);
    }
    end->setState(0);
  }

  List *getPath() {
    List *path = new List();
    Grid *current = maze;
    findPath(current, path);
    return path;
  }

  void printMaze() {
    Grid *j = maze, *k;
    while (j != nullptr) {
      k = j;
      while (k != nullptr) {
        cout << k->getState();
        k = k->getDir(RIGHT);
      }
      cout << endl;
      j = j->getDir(DOWN);
    }
  }

private:
  Grid *maze;

  bool findPath(Grid *current, List *path) {
    if (current == nullptr || current->getState() == 1)
      return false;

    path->addElement(current);
    current->setState(2); // Mark as visited

    if (current->getDir(DOWN) == nullptr && current->getDir(RIGHT) == nullptr)
      return true; // Reached the bottom-right corner

    if (findPath(current->getDir(RIGHT), path) ||
        findPath(current->getDir(DOWN), path) ||
        findPath(current->getDir(LEFT), path) ||
        findPath(current->getDir(UP), path)) {
      return true;
    }

    path->removeElement();
    return false;
  }
};

int main() {
  Maze *maze = new Maze();
  maze->printMaze();
  maze->getPath()->printPath();
}
