
---

## ✅ 问题简述

你要在 `n×n` 的棋盘上放 `n` 个皇后，要求满足：

* 每行只能放一个皇后（所以我们一行一行放）
* 每列只能放一个皇后（不能有两个皇后在同一列）
* 任何两皇后不能处在同一条斜线上（主对角线和副对角线）

---

## 🧠 解题核心思路：回溯 + 逐行摆放

我们从第 1 行开始尝试，每一行从第 1 列到第 n 列去尝试放皇后：

* 如果当前列、斜线没冲突 → 就可以放
* 然后递归到下一行
* 如果下一行无法放，就**回溯**回来换列试试

---

## ✅ C++ 代码（每行详细注释）

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;                       // 皇后的数量
vector<int> path;            // 存储当前成功的皇后列号：path[i] = 第i行皇后放在第几列
vector<vector<int>> results; // 所有合法解

// 检查当前行row，尝试把皇后放在第col列是否安全
bool is_safe(int row, int col) {
    for (int i = 0; i < row; ++i) {
        // path[i] 是第 i 行的皇后放在哪一列
        // 不能同一列、不能同对角线
        if (path[i] == col || abs(path[i] - col) == abs(i - row)) {
            return false; // 不安全
        }
    }
    return true; // 没冲突，可以放
}

// 回溯函数：尝试在第 row 行放皇后
void dfs(int row) {
    if (row == n) {
        results.push_back(path); // 如果已经放满 n 行，保存当前解法
        return;
    }

    // 尝试在本行的每一列放皇后
    for (int col = 1; col <= n; ++col) {
        if (is_safe(row, col)) {     // 判断这一列是否安全
            path.push_back(col);     // 把这一列加入当前路径
            dfs(row + 1);            // 尝试递归下一行
            path.pop_back();         // 回溯：撤销这个选择，尝试其他列
        }
    }
}

int main() {
    cin >> n;                         // 输入皇后的数量
    dfs(0);                           // 从第 0 行开始尝试放皇后

    // 输出所有结果
    for (auto &res : results) {
        for (int num : res) {
            cout << num;             // 输出一个解，每个数字表示当前行放在哪列（列编号从1开始）
        }
        cout << endl;                // 每种解法输出一行
    }

    return 0;
}
```

---

## 🧪 输入样例分析

输入：

```
4
```

输出可能是：

```
2413
3142
```

解释：

* 第一种解 `2413` 表示：

  * 第1行 → 第2列
  * 第2行 → 第4列
  * 第3行 → 第1列
  * 第4行 → 第3列

* 每个排列都是一组不冲突的皇后放法。

---

## 🧠 总结回顾

| 步骤        | 解释               |
| --------- | ---------------- |
| 一行一行放皇后   | 避免重复行            |
| 判断是否安全    | 排除列冲突、对角线冲突      |
| 回溯法       | 用 DFS 构造，回退错误的选择 |
| 每次到底就保存答案 | 用 path 记录中间状态    |

---
### 🧠 问题简述

你要解决的是经典的 **八皇后问题** 的一个变种：
我们已经知道一共有 92 组合法的放法，现在：

* **给一个正整数 n（1 ≤ n ≤ 92）**
* 你要输出第 n 个皇后串（皇后串是每行皇后所在的列，从第 1 行到第 8 行）

而所有的皇后串是按照字典序（即当整数）从小到大排序的。

---

## ✅ 解题思路

我们要：

1. 构造所有 **合法的 8 皇后解**
2. 把每个解转化为一个 “皇后串”，即长度为 8 的数字字符串，比如 `15863724`
3. 按照字典序排序所有皇后串
4. 输出第 n 个

---

### 🧠 如何构造合法解？用 **回溯 + DFS**

* 每一行只能放一个皇后
* 每一列只能放一个皇后
* 对角线不能冲突（主对角线：行-列相等；副对角线：行+列相等）

我们用经典的**DFS回溯算法**来递归生成每一组合法的解。

---

## ✅ 完整 C++ 程序（含每行详细注释）

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> queen_solutions;  // 保存所有合法的皇后串
int board[8];                    // board[i] 表示第 i 行的皇后放在第几列（从 1 开始）
bool col[9];                     // col[i] 表示第 i 列是否已经被使用
bool diag1[16];                  // 主对角线：row - col + 7 (范围0~14)
bool diag2[16];                  // 副对角线：row + col (范围0~14)

// 深度优先搜索当前正在放第 row 行的皇后
void dfs(int row) {
    if (row == 8) {
        // 所有 8 行皇后放好后，构造皇后串并保存
        string s;
        for (int i = 0; i < 8; ++i) {
            s += (board[i] + '0');  // 把列号转为字符（因为列是从1到8）
        }
        queen_solutions.push_back(s);
        return;
    }

    // 尝试在当前 row 的每一列放皇后
    for (int c = 1; c <= 8; ++c) {
        if (!col[c] && !diag1[row - c + 7] && !diag2[row + c]) {
            board[row] = c;              // 在第 row 行放置皇后于第 c 列
            col[c] = diag1[row - c + 7] = diag2[row + c] = true;  // 标记冲突区域
            dfs(row + 1);                // 递归放下一行
            col[c] = diag1[row - c + 7] = diag2[row + c] = false; // 回溯：撤销选择
        }
    }
}

int main() {
    int T;
    cin >> T;

    dfs(0);                            // 先生成所有合法的皇后串
    sort(queen_solutions.begin(), queen_solutions.end());  // 按字典序排序

    while (T--) {
        int n;
        cin >> n;
        cout << queen_solutions[n - 1] << endl;  // 输出第 n 个（从 0 开始）
    }

    return 0;
}
```

---

## 🧪 输入输出样例说明

输入：

```
2
1
92
```

输出：

```
15863724
84136275
```

解释：

* 第一组是所有合法八皇后解中，字典序最小的那一个（第1个）
* 第二组是字典序最大的那个（第92个）

---

## ✅ 核心知识点回顾

| 知识点    | 用法说明                                    |
| ------ | --------------------------------------- |
| DFS 回溯 | 用来生成所有合法八皇后解                            |
| 对角线判断  | 主对角线用 `row - col + 7`，副对角线用 `row + col` |
| 皇后串定义  | `board[i]` 表示第 i 行的皇后放在哪一列              |
| 排序     | 排序后第 n 个即为题目所求                          |

---

