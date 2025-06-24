### 🧠 问题简述

给定一个正整数 `n (1 ≤ n ≤ 7)`，将数字 `1~n` 全部排列，按**字典序**输出所有排列结果。每个排列单独一行，数字间用空格分隔。

---

## ✅ 解题思路：全排列 + 字典序输出

我们要列出 `n` 个数字的全排列：

* 使用 **回溯法（DFS）** 生成所有排列
* 为了保证是**字典序**输出，从小到大选择数字（比如从 1\~n 枚举）

---

### ✨ 关键点

* **字典序排列**：本质上是从左往右，数字越小的排列越靠前
* **回溯**核心：每一层递归挑选一个没被选过的数字加入路径
* 使用 `used[]` 数组记录哪些数字已经使用过

---

## ✅ C++ 实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> path;      // 存放当前排列路径
bool used[10] = {0};   // 标记每个数字是否被使用过

void dfs(int depth) {
    if (depth == n) {
        // 输出当前路径
        for (int i = 0; i < n; ++i) {
            cout << path[i];
            if (i < n - 1) cout << " ";
        }
        cout << endl;
        return;
    }

    // 按照字典序枚举1~n
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(i);

            dfs(depth + 1);

            path.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}
```

---

## 🧪 输入输出样例

输入：

```
3
```

输出：

```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

---

## 🔄 时间复杂度分析

全排列一共有 $n!$ 种情况，因此总时间复杂度为：

$$
O(n \cdot n!) 
$$

（每次排列打印需 O(n)，总共 n! 个排列）

---
