#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class numberguessing {
private:
  int value;
  int times;

public:
  numberguessing() : times(0) {}
  void Set(int v) { value = v; }

  int Guesser(int v) {
    times++;
    if (value < v)
      return -1;
    else if (value > v)
      return 1;
    else
      return 0;
  }

  int Time() { return times; }

  void Reset() { times = 0; }
};
