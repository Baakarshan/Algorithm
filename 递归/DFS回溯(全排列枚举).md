
---

### ✅ 一、题目要求简述

给定整数 n（1 ≤ n ≤ 9），你要输出 1 \~ n 所有的排列，每行一个排列，排列内数字升序排列，相邻数字用空格分隔；所有排列按字典序排序。

---

### ✅ 二、解题思路（用 DFS + 回溯法）

#### ✅ 使用 DFS（深度优先搜索）+ 回溯：

* 我们从空的排列出发，每次在未被使用的数字中选择一个放入当前排列。
* 直到选够 n 个数字，输出当前排列。
* 注意使用 `used` 数组标记数字是否被选过，防止重复。
* 用 `sort` 或原始升序遍历来保证字典序输出。

---

### ✅ 三、C++ 代码（含详细注释）

```cpp
#include <iostream>
#include <vector>
using namespace std;

int n;                      // 数字的总数
vector<int> path;           // 当前构造的排列
bool used[10];              // 标记数字是否使用过

// 回溯函数：构造全排列
void dfs() {
    if (path.size() == n) {  // 如果当前排列长度等于 n，说明构造完成
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";  // 每个数前加空格（第一个数除外）
            cout << path[i];         // 输出当前排列的数
        }
        cout << endl;
        return;
    }

    for (int i = 1; i <= n; ++i) {   // 枚举从 1 到 n 的数字
        if (!used[i]) {             // 如果数字 i 没有被使用
            used[i] = true;         // 选择数字 i
            path.push_back(i);      // 放入当前路径
            dfs();                  // 递归构造下一个位置
            path.pop_back();        // 回溯：撤销选择
            used[i] = false;        // 标记 i 为未使用
        }
    }
}

int main() {
    cin >> n;        // 输入 n
    dfs();           // 启动回溯生成所有排列
    return 0;
}
```

---

### ✅ 四、运行示例（n = 3）

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

### ✅ 五、复杂度分析

* **时间复杂度：** O(n!)，因为 n 个数的全排列就是 n! 种。
* **空间复杂度：** O(n)，用于递归栈和路径存储。

---

---

## 🔍 问题简述（n = 3）

我们要用 DFS 构造所有由 `[1, 2, 3]` 组成的不重复排列。每一步我们选择一个**未使用的数**放进排列中，直到长度为 3 即输出。

---

## 🌲 DFS 搜索树展开（n = 3）

我们从空数组开始递归构造，使用 `path` 保存当前构造的排列，`used[i]` 表示数字 `i` 是否用过。

```
dfs()
├── 选择 1（path = [1]）
│   ├── 选择 2（path = [1,2]）
│   │   └── 选择 3（path = [1,2,3]）→ 输出 1 2 3
│   └── 选择 3（path = [1,3]）
│       └── 选择 2（path = [1,3,2]）→ 输出 1 3 2
├── 选择 2（path = [2]）
│   ├── 选择 1（path = [2,1]）
│   │   └── 选择 3（path = [2,1,3]）→ 输出 2 1 3
│   └── 选择 3（path = [2,3]）
│       └── 选择 1（path = [2,3,1]）→ 输出 2 3 1
└── 选择 3（path = [3]）
    ├── 选择 1（path = [3,1]）
    │   └── 选择 2（path = [3,1,2]）→ 输出 3 1 2
    └── 选择 2（path = [3,2]）
        └── 选择 1（path = [3,2,1]）→ 输出 3 2 1
```

---

## ✅ 最终输出顺序

```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

这个顺序正好是字典序输出的所有排列。

---

## 📌 小结

这就是典型的 DFS + 回溯：

* 每一层 DFS 表示选择一个位置；
* 枚举所有没用过的数字作为当前位；
* 用完一个数字后，递归探索；
* 递归回来后撤销选择，继续下一个分支。

