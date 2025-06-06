#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, fee;
  cin >> n >> fee;
  vector<int> prices(n);
  for (int i = 0; i < n; ++i)
    cin >> prices[i];

  /*
  vector<int> cash(n), hold(n);
  cash[0] = 0;
  hold[0] = -prices[0];

  for (int i = 1; i < n; ++i) {
    cash[i] = max(cash[i - 1], hold[i - 1] + prices[i] - fee);
    hold[i] = max(hold[i - 1], cash[i - 1] - prices[i]);
  }
  */

  // 初始化兩個狀態：
  // cash 表示當前不持有股票的最大利潤
  // hold 表示當前持有股票的最大利潤
  int cash = 0;
  int hold = -prices[0]; // 第一天買入，手上有股票，利潤為負

  for (int i = 1; i < n; ++i) {
    // 更新狀態：
    // 如果今天賣出股票：我們昨天手上有股票 hold，加上今天股價，扣除手續費
    // 和昨天就沒持股的 cash 比較，取較大者
    cash = max(cash, hold + prices[i] - fee);

    // 如果今天買入股票：我們昨天手上沒股票 cash，扣今天股價
    // 和昨天就有持股的 hold 比較，取較大者
    hold = max(hold, cash - prices[i]);
  }

  // 最後答案是我們**最後一天不持股時的最大利潤**
  cout << cash << endl;

  return 0;
}
