#include <iostream>
#include <map> // For memoization approach, if chosen
#include <vector>
#define ll long long

ll climb(int n) {
  if (n < 0)
    return 0;
  static std::vector<ll> dp(1, -1);
  dp.resize(n + 1, -1);
  if (n == 0)
    return 1;
  if (dp[n] != -1)
    return dp[n];
  return dp[n] = climb(n - 1) + climb(n - 2) + climb(n - 3);
}

// ##### 學生的實作區域 START #####
ll count_ways_to_climb(int n) {
  if (n < 0)
    return 0;
  ll ways = 0;
  std::vector<ll> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    if (i >= 1)
      dp[i] += dp[i - 1];
    if (i >= 2)
      dp[i] += dp[i - 2];
    if (i >= 3)
      dp[i] += dp[i - 3];
  }
  return ways = dp[n];
}
// ##### STUDENT'S IMPLEMENTATION AREA END #####
// ##### 學生的實作區域 END #####

int main() { // Renamed to avoid conflict if other mains are present
  using namespace std;
  cout << "--- Fibonacci / Climbing Stairs ---" << endl;

  cout << "\n--- Climbing Stairs (1, 2, or 3 steps) ---" << endl;
  cout << "Ways to climb 0 stairs: " << count_ways_to_climb(0)
       << endl; // Expected: 1
  cout << "Ways to climb 1 stair: " << count_ways_to_climb(1)
       << endl; // Expected: 1
  cout << "Ways to climb 2 stairs: " << count_ways_to_climb(2)
       << endl; // Expected: 2
  cout << "Ways to climb 2 stairs: " << count_ways_to_climb(3)
       << endl; // Expected: 4
  cout << "Ways to climb 4 stairs: " << count_ways_to_climb(4)
       << endl; // Expected: 1+2+4 = 7
  cout << "Ways to climb 5 stairs: " << count_ways_to_climb(5)
       << endl; // Expected: 2+4+7 = 13
  return 0;
}
