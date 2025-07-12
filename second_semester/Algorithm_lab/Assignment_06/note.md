## **Pseudo-Polynomial Time 的 DP 問題**

這些問題的 DP 解法依賴於「輸入值大小」，而不是「輸入長度（bit 數）」。

| **問題類型**                      | **時間複雜度（典型）** | **原因 / 說明**            |
| --------------------------------- | ---------------------- | -------------------------- |
| 0/1 Knapsack                      | O(n * W)               | W 是容量的實際值           |
| Subset Sum                        | O(n * target)          | target 是實際總和          |
| Partition Problem                 | O(n * totalSum)        | 類似 Subset Sum            |
| Bounded Knapsack                  | O(n * W * c_max)       | c_max 是 copy 數量的實際值 |
| Coin Change (#ways)               | O(n * amount)          | amount 是硬幣總和          |
| Integer Knapsack (value-based DP) | O(n * V)               | V 是價值總和               |
| Bellman-Ford (整數邊權)           | O(V * E * W)           | W 為邊權最大值             |

## **Polynomial Time 的 DP 問題**

這些問題的時間複雜度是對「輸入長度」的多項式，不受值大小影響。

| **問題類型**                         | **時間複雜度（典型）** | **原因 / 說明**  |
| ------------------------------------ | ---------------------- | ---------------- |
| Longest Common Subsequence (LCS)     | O(n * m)               | 純粹比對字元     |
| Edit Distance (Levenshtein)          | O(n * m)               | 純粹字元操作     |
| Matrix Chain Multiplication          | O(n³)                  | 括號加總順序問題 |
| Longest Increasing Subsequence (LIS) | O(n log n)             | 二分搜尋做法     |
| Rod Cutting (長度為 n)               | O(n²)                  | 遍歷切割點       |
| Palindromic Substring Counting       | O(n²)                  | 比對子字串       |
| Number of ways to climb stairs (fib) | O(n)                   | 沒有值大小參與   |

