/*
#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n) {
  *p = (int **)malloc(m * sizeof(int *)); // 為行指標分配記憶體
  for (int i = 0; i < m; i++) {
    (*p)[i] = (int *)malloc(n * sizeof(int)); // 為每一行分配記憶體
  }
}

int main() {
  int **array; // 二維陣列指標
  int j, k;

  // 動態分配 5x10 的二維陣列
  allocArray(&array, 5, 10);

  // 初始化二維陣列
  for (j = 0; j < 5; j++)
    for (k = 0; k < 10; k++)
      array[j][k] = j * 10 + k;

  // 輸出每個元素的地址和值
  for (j = 0; j < 5; j++) {
    for (k = 0; k < 10; k++) {
      printf("Address: %p, Value: %d\n", &(array[j][k]), array[j][k]);
    }
  }
  // 釋放動態記憶體
  for (j = 0; j < 5; j++) {
    free(array[j]); // 釋放每一行的記憶體
  }
  free(array); // 釋放行指標的記憶體

  return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n) {
  // 分配連續的 m * n 空間
  *p = (int **)malloc(m * sizeof(int *));
  int *data = (int *)malloc(m * n * sizeof(int));

  for (int i = 0; i < m; i++) {
    (*p)[i] = data + i * n;
  }
}

int main() {
  int **array;
  int j, k;

  // 動態分配 5x10 的二維陣列
  allocArray(&array, 5, 10);

  // 初始化二維陣列
  for (j = 0; j < 5; j++)
    for (k = 0; k < 10; k++)
      array[j][k] = j * 10 + k;

  // 輸出每個元素的地址和值
  for (j = 0; j < 5; j++) {
    for (k = 0; k < 10; k++) {
      printf("Address: %p, Value: %d\n", &(array[j][k]), array[j][k]);
    }
  }

  // 釋放記憶體
  free(array[0]); // 釋放連續的數據空間
  free(array);    // 釋放行指標的記憶體

  return 0;
}
