// output n numbers in fibonacci sequence.

#include <iostream>
using namespace std;

/*
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
  bool first = true;
  for (int i = 0; i < n; i++) {
    if (!first)
      std::cout << ", ";
    std::cout << a[i];
    first = false;
  }

  delete[] a;
  return 0;
} */

int main() {
  int n;
  cin >> n;
  int temp1, temp2, ans;
  temp1 = 0;
  temp2 = 1;

  if (n == 0)
    exit(1);

  cout << temp1 << '\n';
  if (n == 1)
    exit(1);

  cout << temp2 << '\n';
  if (n == 2)
    exit(1);

  int index = 2;
  while (index != n) {
    ans = temp2 + temp1;
    cout << ans << '\n';

    temp1 = temp2;
    temp2 = ans;
    index++;
  }
}
