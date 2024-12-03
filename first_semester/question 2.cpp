#include <cstdlib>
#include <iostream>

using namespace std;

template <class T> class Memory {
public:
  /*
  // 分配大小為 m x n 的二維陣列
  static T **allocArray(int m, int n) {
    // 分配指向行的指標
    T **array = (T **)malloc(m * sizeof(T *));

    // 為每一行分配空間
    for (int i = 0; i < m; i++) {
      array[i] = (T *)malloc(n * sizeof(T));
    }

    return array;
  }*/

  static T **allocArray(int m, int n) {
    T **a = new T *[m];
    T *all = new T[m * n];

    for (int i = 0; i < m; i++) {
      a[i] = &all[i * n];
    }
    return a;
  }
};

int main() {
  int **array;
  array = Memory<int>::allocArray(5, 10); // 分配 5x10 的二維陣列

  int j, k;

  // 初始化陣列
  for (j = 0; j < 5; j++)
    for (k = 0; k < 10; k++)
      array[j][k] = j * 10 + k;

  // 打印陣列
  for (j = 0; j < 5; j++) {
    for (k = 0; k < 10; k++)
      cout << array[j][k] << " ";
    cout << endl;
  }

  // 釋放記憶體
  delete[] array[0];
  delete[] array;
  return 0;
}
