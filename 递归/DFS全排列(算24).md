
---

### ✅ C++ 代码：回溯 + 全排列 + 浮点判断

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 判断是否约等于 24（避免浮点数误差）
const double TARGET = 24.0;
const double EPS = 1e-6;

// 递归函数，尝试所有组合方式
bool dfs(vector<double>& nums) {
    int n = nums.size();
    if (n == 1) {
        return fabs(nums[0] - TARGET) < EPS; // 判断是否约等于 24
    }
    // 枚举任意两个数进行四种运算
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            // 取出 nums[i], nums[j]，准备合并计算
            vector<double> next;
            for (int k = 0; k < n; ++k) {
                if (k != i && k != j) next.push_back(nums[k]);
            }

            // 枚举四种操作
            for (int op = 0; op < 4; ++op) {
                // 加法和乘法是交换律，避免重复
                if ((op == 0 || op == 2) && i > j) continue;

                double result = 0;
                if (op == 0) result = nums[i] + nums[j];
                if (op == 1) result = nums[i] - nums[j];
                if (op == 2) result = nums[i] * nums[j];
                if (op == 3) {
                    if (fabs(nums[j]) < EPS) continue; // 除数不能为 0
                    result = nums[i] / nums[j];
                }

                next.push_back(result);
                if (dfs(next)) return true;
                next.pop_back(); // 回溯
            }
        }
    }
    return false;
}

int main() {
    while (true) {
        vector<int> input(4);
        bool end = true;
        for (int i = 0; i < 4; ++i) {
            cin >> input[i];
            if (input[i] != 0) end = false;
        }
        if (end) break;

        sort(input.begin(), input.end());
        bool found = false;
        // 全排列所有顺序
        do {
            vector<double> nums;
            for (int x : input) nums.push_back(x);
            if (dfs(nums)) {
                found = true;
                break;
            }
        } while (next_permutation(input.begin(), input.end()));

        cout << (found ? "YES" : "NO") << endl;
    }
    return 0;
}
```

---

### ✅ 特点与优势说明

* 用 `vector<double>` 来处理浮点运算，保证除法的正确性。
* 用 DFS 枚举所有两两组合的运算方式。
* 用 `fabs(a - b) < EPS` 解决浮点误差问题。
* 用 `next_permutation` 生成所有数字顺序，确保不同排列被覆盖。

---

### ✅ 示例运行（样例）

输入：

```
5 5 5 1
1 1 4 2
0 0 0 0
```

输出：

```
YES
NO
```

---

这个问题是经典的「24 点问题」：给出 4 个正整数（每个小于 10），问是否可以通过加减乘除和括号组合成表达式，使得其值为 24。可以改变数字顺序。

---

### 🧠 解题思路（完整文字讲解）：

我们需要考虑以下几点：

#### ✅ 核心目标

从 4 个数出发，通过：

* 任意顺序排列（4! = 24种顺序）
* 任意加括号的方式（多种组合）
* 加、减、乘、除这 4 种运算符
* 判断最终结果是否可以等于 24

#### ✅ 步骤详解

我们使用 **回溯法（DFS）** 递归尝试所有组合：

1. **初始状态**：我们有一个数组 `nums` 里放着当前可用的数，初始为输入的那4个数。

2. **终止条件**：

   * 如果数组里只剩下一个数：检查这个数是否与24足够接近（考虑浮点误差）。

3. **尝试所有的组合**：

   * 从当前数组中任选两个数，进行 +, -, \*, / 四种操作：

     * 计算结果 result。
     * 创建一个新数组：把刚才两个数删去，加入 result。
     * 对新数组递归调用 DFS。
     * 回溯，恢复原数组。

4. **注意细节**：

   * 除法时除数不能为 0。
   * 因为除法涉及浮点计算，判断是否等于 24 时用一个小误差容差（如 `fabs(x - 24) < 1e-6`）避免误差问题。

5. **数字顺序可以变**：

   * 所以对输入数组先做一个全排列（24种）进行遍历，每个排列都递归搜索。

---

### ✅ 例子手动模拟

对输入：`5 5 5 1`

排列为：`5, 5, 5, 1`，可尝试表达式：

```
5 * (5 - 1 / 5) = 5 * (4.8) = 24
```

成立 → 输出 YES

对输入：`1 1 4 2`

无论排列与组合都不会得到 24 → 输出 NO

---

### ✅ 结论

我们使用：

* **全排列** 来尝试数字顺序
* **回溯/递归** 来遍历所有可能操作顺序与组合
* **浮点数判断技巧** 来避免误差

