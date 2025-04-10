#include <cmath>
#include <iostream>

// epi = epsilon（ε）
// NAN = Not A Number (unvalid and doesn't exist
double solve(double (*f)(double), double a, double b, double val, double epi) {
  if ((f(a) - val) * (f(b) - val) > 0)
    return NAN;
  double mid = (a + b) * 0.5;
  if (abs(f(mid) - val) <= epi)
    return mid;
  else if ((f(a) - val) * (f(mid) - val) <= 0)
    return solve(f, a, mid, val, epi);
  else
    return solve(f, mid, b, val, epi);
}

double f(double x) { return x * x; }
int main() { std::cout << solve(f, 0, 2, 3, 0.0001); }
