#include <algorithm>
#include <iostream>
#include <vector>

struct Activity {
  int s, e;
};

bool a_comp(const Activity &a, const Activity &b) { return (a.e < b.e); }

int max_schedule(std::vector<Activity> A) {
  std::sort(A.begin(), A.end(), a_comp);
  int count = 1;
  int end = A[0].e;
  for (int i = 1; i < A.size(); ++i) {
    if (end > A[i].s) // 下一個開始的時間不超過上一個結束的時間
      continue;
    end = A[i].e; // 更新結束的時間
    ++count;
  }
  return count;
}

// Returns the minimum number of activities required to cover the interval [S,
// T)
int min_cover(std::vector<Activity> A, int S, int T) {
  // Sort activities by start time in ascending order
  std::sort(A.begin(), A.end(),
            [](const Activity &a, const Activity &b) { return a.s < b.s; });

  int count = 0;    // Number of activities selected
  int now = S;      // Current time point we need to cover
  int i = 0;        // Index to scan through the activity list
  int n = A.size(); // Total number of activities

  // Keep selecting activities until we cover the interval [S, T)
  while (now < T) {
    int max_end = -1; // Farthest reachable end time from current point

    // Iterate over all activities that start at or before 'now'
    while (i < n && A[i].s <= now) {
      max_end = std::max(max_end, A[i].e); // Pick the one that ends the latest
      i++;
    }

    // If no activity can extend the coverage, return -1 (impossible)
    if (max_end <= now)
      return -1;

    // Move the current point forward to the end of the selected activity
    now = max_end;
    count++; // One more activity selected
  }

  return count; // Return the minimum number of activities used
}

// Return the minimum number of rooms needed to schedule all activities
int min_rooms(std::vector<Activity> A) {
  std::vector<std::pair<int, int>> events;

  for (auto &act : A) {
    events.emplace_back(act.s, +1); // start event
    events.emplace_back(act.e, -1); // end event
  }

  // Sort by time; if equal, end (-1) before start (+1)
  std::sort(events.begin(), events.end(), [](auto &a, auto &b) {
    return a.first == b.first ? a.second < b.second : a.first < b.first;
  });

  int ongoing = 0;   // current number of active rooms
  int max_rooms = 0; // maximum rooms used at any time

  for (auto &[time, delta] : events) {
    ongoing += delta;
    max_rooms = std::max(max_rooms, ongoing);
  }

  return max_rooms;
}

int main() {
  // Example test case
  std::vector<Activity> A = {{0, 4}, {2, 6}, {4, 8}, {5, 10}, {6, 9}, {9, 10}};

  int result1 = max_schedule(A);
  std::cout << "Maximum activities to cover: " << result1 << std::endl;

  int S = 0, T = 10;

  int result2 = min_cover(A, S, T);
  if (result2 != -1)
    std::cout << "Minimum activities to cover [" << S << ", " << T
              << "): " << result2 << std::endl;
  else
    std::cout << "Cannot cover the full interval with given activities."
              << std::endl;

  int result3 = min_rooms(A);
  std::cout << "Minimum number of rooms needed: " << result3 << std::endl;
  return 0;
}
