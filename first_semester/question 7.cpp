#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 10

using namespace std;

class Node {
public:
  Node() { Node(0, 0); }
  Node(int r, int c) {
    row = r;
    col = c;
  }
  int getRow() { return row; }
  int getCol() { return col; }
  void setRow(int r) {
    if (r >= 0 && r < SIZE)
      row = r;
  }
  void setCol(int c) {
    if (c >= 0 && c < SIZE)
      col = c;
  }

private:
  int col, row;
};

class List {
public:
  List() { top = 0; }
  /*
  function addElement
  Insert an element from list
  */
  void addElement(int r, int c) {
    data[top].setRow(r);
    data[top].setCol(c);
    top++;
  }
  /*
  function removeElement
  remove an element from list and return a pointer point to the element.
  If list is empty, return NULL.
  */
  Node *removeElement() {
    if (top > 0) {
      top--;
      return &data[top];
    }
    return nullptr;
  }

  void printList() {
    int j;
    for (j = 0; j < top; j++) {
      cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")"
           << endl;
    }
  }

private:
  Node data[SIZE * SIZE];
  int top;
};

class Maze {
public:
  Maze() { initMaze(SIZE); }
  /*
  function initMaze
  Alocate a 2-D array with s * s sizes as the map of maze.
  Inside the maze where 0 represent empty space and 1 represent wall.
  [0][0] is start point and [s - 1][s - 1] is finish point.
  Randomly generate 20% wall in the maze.
  Make sure [0][0] and [s - 1][s - 1] are 0

  動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
  陣列中 0 的值表示可以移動的空間， 1 表示牆壁
  [0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
  請在迷宮中加入 20% 的牆壁
  然後確定起點跟終點都是可以移動的位置
  */
  void initMaze(int s) {

    srand(time(0)); // 初始化隨機數生成器
    // 動態配置 s * s 的迷宮
    maze = new int *[s];
    visited = new bool *[s];
    for (int i = 0; i < s; ++i) {
      maze[i] = new int[s];
      visited[i] = new bool[s];
    }

    // 填充迷宮，隨機生成 20% 的牆壁
    for (int i = 0; i < s; ++i) {
      for (int j = 0; j < s; ++j) {
        if ((rand() % 100) < 20) // 20% 的機會生成牆壁
          maze[i][j] = 1;        // 1 代表牆壁
        else
          maze[i][j] = 0; // 0 代表空地
        visited[i][j] = false;
      }
    }

    // 確保起點和終點是可以移動的空地
    maze[0][0] = 0;         // 起點
    maze[s - 1][s - 1] = 0; // 終點
  }

  /*
  function getPath
  This function will find a path between start point and finish point.
  Return a list content the path information inside.
  If there is no path between two point then the list will be empty.

  這個函數會找到起點到終點間的一條路徑
  回傳一個 list 包含著路徑的資訊
  如果找不到路徑的話 list 就會是空的
  */
  List *getPath() {
    List *path = new List();
    if (dfs(0, 0, path))
      return path;
    else {
      delete path;
      return new List();
    }
  }

  void printMaze() {
    int j, k;
    for (j = 0; j < SIZE; j++) {
      for (k = 0; k < SIZE; k++) {
        if (maze[j][k] == 0)
          cout << " ";
        else if (maze[j][k] == 1)
          cout << "*";
      }
      cout << "\n";
    }
  }

  ~Maze() {
    for (int i = 0; i < SIZE; i++) {
      delete[] maze[i];
      delete[] visited[i];
    }
    delete[] maze;
    delete[] visited;
  }

private:
  int **maze;
  bool **visited;

  const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  bool isValid(int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && maze[r][c] == 0 &&
           !visited[r][c];
  }

  bool dfs(int r, int c, List *path) {
    path->addElement(r, c);
    if (r == SIZE - 1 && c == SIZE - 1) {
      return true;
    }
    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
      int newR = r + dir[i][0];
      int newC = c + dir[i][1];

      if (isValid(newR, newC) && dfs(newR, newC, path))
        return true;
    }

    path->removeElement();
    return false;
  }
};

int main() {
  Maze *maze = new Maze();
  maze->printMaze();
  maze->getPath()->printList();
}
