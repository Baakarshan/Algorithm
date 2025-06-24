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


### 🧠 问题简述

你给我一个**由不同小写字母组成的字符串**（长度 2\~8），比如 `"abc"`，我要输出它的**所有字母排列**（即全排列），并且要求**按字典序从小到大**输出。

---

## ✅ 解题思路：回溯法（DFS）生成全排列

这个问题是**排列组合中的全排列问题**，我们要做的是：

* 把所有字符的排列枚举出来（用**回溯法/深度优先搜索**）
* 在每一层选择还没有使用过的字符
* 最后输出排列时按**字典序**排好

---

### 🎯 为什么选 DFS（深度优先搜索）？

因为我们要一条路一条路构建排列，每次选一个字符放进“排列路径”，再递归往下选择，直到长度和输入字符串一样为止。

---

## ✅ C++ 实现（带注释）

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string s;            // 输入字符串
vector<bool> used;   // 用于标记哪些字符已经用过
string path;         // 当前构建的排列路径
vector<string> res;  // 所有排列结果

void dfs(int depth) {
    if (depth == s.size()) {
        res.push_back(path);
        return;
    }

    for (int i = 0; i < s.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(s[i]);

            dfs(depth + 1);

            path.pop_back();      // 回溯
            used[i] = false;
        }
    }
}

int main() {
    cin >> s;
    sort(s.begin(), s.end());    // 字符排序，确保生成的是字典序顺序

    used = vector<bool>(s.size(), false);
    dfs(0);

    for (const auto &perm : res) {
        cout << perm << endl;
    }

    return 0;
}
```

---

## 🧪 输入输出示例

输入：

```
abc
```

输出（按字典序）：

```
abc
acb
bac
bca
cab
cba
```

---

## 🧠 核心点回顾

| 操作                         | 原因                  |
| -------------------------- | ------------------- |
| `sort(s.begin(), s.end())` | 保证回溯时从小字符开始，确保结果字典序 |
| `used[i]`                  | 避免一个字符重复出现在同一个排列中   |
| `dfs(depth + 1)`           | 递归推进，直到构成一个完整排列     |
| `path.pop_back()`          | 回溯，撤销选择，尝试下一个字符     |

---

