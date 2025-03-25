// output n numbers in fibonacci sequence.

#include <iostream>

// 0, 1, 1, 2, 3
void fib(int n, int *a) {
  if (n <= 2) {
    a[n - 1] = n - 1;
    return;
  }
  a[0] = 0;
  a[1] = 1;
  for (int i = 2; i < n; i++) {
    a[i] = a[i - 1] + a[i - 2];
  }
}

int main() {
  int n;
  std::cin >> n;
  int *a = new int[n];

  fib(n, a);
  for (int i = 0; i < n; i++)
    std::cout << a[i] << ", ";
  delete[] a;
  return 0;
}
