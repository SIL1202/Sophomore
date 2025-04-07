#include <iostream>
using namespace std;

int GCDCounters[8] = {0};

int GCD(int a, int b) {
  int temp;
  GCDCounters[2] += 1;                      /*line: 1*/
  while ((GCDCounters[2] += 1) && b != 0) { /*line: 2*/
    // 因為 && 的優先級較 += 高，所以要加括號
    temp = a % b;
    GCDCounters[3] += 1; /*line: 3*/
    a = b;
    GCDCounters[4] += 1; /*line: 4*/
    b = temp;
    GCDCounters[5] += 1; /*line: 5*/
    GCDCounters[6] += 1;
  } /*line: 6*/

  GCDCounters[7] += 1;
  return a; /*line: 7*/
}

int ProfileGCD() {
  int ans = 0;
  ans += GCDCounters[1] * 1; // Allocate static variable
  ans += GCDCounters[2] * 2; // Compare and Branch
  ans += GCDCounters[3] * 2; // Modulo and assign value
  ans += GCDCounters[4] * 1; // Assign value
  ans += GCDCounters[5] * 1; // Assign value
  ans += GCDCounters[6] * 1; // Jump back to loop begin
  ans += GCDCounters[7] * 1; // Return value
  return ans;
}

int Classify(int a) {
  // Check a>1 first:
  if (a > 1)
    return 3;
  else if (a == 0)
    return 1;
  else
    return 2; // covers the case a == 1
}

int main() {
  int a, b;
  // a = 3;
  // b = 24;

  // cin >> a >> b;
  cout << "Classify = " << Classify(GCD(a, b)) << endl;
  cout << "ProfileGCD = " << ProfileGCD() << endl;

  return 0;
}
