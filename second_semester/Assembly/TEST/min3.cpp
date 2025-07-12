#include <iostream>

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int main() {
  int a0, a1, a2;
  std::cin >> a0 >> a1 >> a2;
  std::cout << min(a0, min(a1, a2));
}
