# 🎓 Crediti ed Esami — Exam Scheduling Optimizer

A **dynamic programming** solution in C that finds the minimum time to pass all university exams, using a credit-based system to strategically skip costly ones.

> 📚 Algorithms & Data Structures — University Project (2024/2025)  
> Author: **Davide Corso**

---

## The Problem

A university organizes **N exams** in sequence. Each exam `i` requires time `T_i` to complete and awards `C_i` credits. A student can accumulate up to **K credits** and spend exactly K to **skip any exam** (passing it in zero time).

**Goal:** find the **minimum total time** to pass all N exams.

### Constraints
- `N ≤ 1,000,000` exams
- `K ≤ 50` max credits
- Credits cannot exceed K (excess is lost)
- Student starts with 0 credits

## Solution

The algorithm uses **bottom-up dynamic programming** with two rolling arrays of size `K+1`, where each index represents the number of credits held and each cell stores the minimum time to reach that state.

For each exam, the algorithm evaluates:
1. **Take the exam** → spend `T_i` time, gain `C_i` credits
2. **Skip the exam** (if credits = K) → spend 0 time, lose K credits

By comparing all possible paths and keeping only the optimal time per credit state, the solution avoids redundant computation.

### Complexity
| | Complexity |
|---|---|
| **Time** | `O(N × K)` |
| **Space** | `O(K)` |

## Example

```
Input:
3 4
1 1
2 3
4 1

Output: 3
```

Pass exams 1 and 2 (time = 1 + 2 = 3, credits = 4), then skip exam 3 for free.

## Build & Run

```bash
gcc -O2 -o exam_scheduler main.c
./exam_scheduler < examples/input.txt
```

## Project Structure

```
├── main.c                  # Final optimized solution
├── examples/
│   ├── input.txt           # Sample input (10 exams, K=5)
│   └── output.txt          # Expected output: 1156
└── docs/
    └── assignment.pdf      # Original problem statement
```

## Evolution

The solution went through 4 iterations before reaching the final version:

| Version | Approach | Time | Space | Issue |
|---------|----------|------|-------|-------|
| 1 | Recursion | O(2ᴺ) | O(N) | No DP, exponential blowup |
| 2 | Array indexed by time | O(N²) | O(ΣTᵢ) | Huge memory footprint |
| 3 | Matrix indexed by credits | O(N×K) | O(N×K) | Unnecessary row storage |
| **4** | **Rolling arrays by credits** | **O(N×K)** | **O(K)** | **✅ Final solution** |

## License

All rights reserved. This project is shared for portfolio and educational purposes only.
