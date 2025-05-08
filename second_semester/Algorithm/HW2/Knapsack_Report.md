# Knapsack Problem: Algorithm Comparison Report

## 1. Introduction

This report evaluates and compares three algorithms for solving the 0/1 Knapsack problem:

- **Bottom-Up Dynamic Programming**
- **Top-Down Dynamic Programming with Memoization**
- **Greedy Algorithm (by value/weight ratio)**

Each algorithm is tested on seven representative datasets to assess correctness, performance, and applicability.

---

## 2. Test Case Overview

| Test Case | Description                        | n   | Weight Range    | Special Trait                     |
|-----------|------------------------------------|-----|------------------|-----------------------------------|
| T0        | Small case                         | 10  | 1–10             | Baseline                         |
| T1        | Medium-scale                       | 100 | 1–10             | Time complexity grows            |
| T2        | Large-scale                        | 500 | 1–100            | Exposes performance limits       |
| T3        | Equal weights                      | 30  | all 1            | Greedy expected to match DP      |
| T4        | Wide weight range                  | 30  | 1–1000           | Greedy likely to deviate         |
| T5        | profit == weight                   | 30  | 1–100            | Greedy CP ratio uniform          |
| T6        | All items too large                | 10  | 100–1000         | No solution (expect profit 0)    |

---

## 3. Experimental Results

| Case | Bottom-Up Profit | BU Time (us) | Top-Down Profit | TD Time (us) | Greedy Profit | G Time (us) |
|------|------------------|--------------|------------------|--------------|----------------|-------------|
| T0   | 3921             | 19           | 3921             | 8            | 3770           | 7           |
| T1   | 40729            | 952          | 40729            | 928          | 40729          | 48          |
| T2   | 199335           | 108190       | 199335           | 113343       | 199270         | 131         |
| T3   | 9789             | 17           | 9789             | 9            | 9789           | 7           |
| T4   | 11293            | 2927         | 11293            | 2334         | 11293          | 15          |
| T5   | 664              | 325          | 664              | 262          | 655            | 4           |
| T6   | 0                | 18           | 0                | 0            | 0              | 2           |

---

## 4. Analysis

### Correctness:
- Bottom-Up and Top-Down always return the same (optimal) value.
- Greedy fails to find the optimal solution in T0, T2, and T5.
- In T3 and T5 (uniform or CP-equal), Greedy performs identically.

### Performance:
- **Greedy** is fastest in all cases.
- **Bottom-Up** scales poorly with large W and n (e.g., T2).
- **Top-Down** performs similarly but uses less memory when subproblems are sparse.

---

## 5. Conclusion

- **Use DP (Bottom-Up/Top-Down)** when accuracy is essential, and time/memory is acceptable.
- **Use Greedy** when speed is prioritized and approximate solutions are acceptable.
- Greedy performs well when item values and weights are balanced or uniform.

---