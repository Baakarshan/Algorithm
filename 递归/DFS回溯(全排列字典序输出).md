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


---

## 🧠 一、你要解决的问题是什么？

你给我一个字符串，例如 `"abc"`。这个字符串：

* 每个字符都不一样（无重复字母）
* 我需要把这些字母所有可能的**排列顺序**都列出来
* 要求按照**字典序**排序输出

---

### 📚 举例：输入 `"abc"` 会有哪些排列？

排列就是把每个字符换位置得到不同顺序：

```
abc
acb
bac
bca
cab
cba
```

是不是 3 个字母就有 6 个排列？对的，因为排列数是 `3! = 6`
那如果是 4 个字母，就是 `4! = 24` 个排列！

---

## ✅ 二、怎么生成这些排列？

这时候就用到了**回溯算法（Backtracking）**，也叫**深度优先搜索（DFS）**。

你可以把这个过程想象成：

> “我要选一个顺序，把每个字母都用一次、不重复，拼成一行。”

---

### 📦 模拟“选字母”的过程（n = 3）

你有一盒字母：`a b c`

你想排一个长度为 3 的序列，那可以这么做：

1. 第一位可以选 a、b 或 c
2. 假设第一位选了 `a`，那剩下还有 `b` 和 `c` 可选
3. 第二位选了 `b`，那只剩 `c`，它就是第三位
   → 得到 `a b c`

你每做一次这样的“选→剩下→继续选”，直到长度满足为止。

这就是**深度优先搜索（DFS）**：每一条路走到底，然后回头再换。

---

## 🔁 三、程序怎么写这个“走”的过程？

我们写一个函数 `dfs(当前选了几位)`，它会：

1. 如果选满了（比如已经选了 3 位），就把当前排列结果存下来
2. 否则：

   * 从头到尾把每个字符试一遍
   * 如果这个字符没用过，就试着放进去
   * 然后进入下一层递归继续选
   * 递归完回来后，要“撤销刚才选的字符”，再试别的字符（这叫“回溯”）

---

## ✅ 四、详细代码解释（超细）

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string s;                // 输入的字符串
vector<bool> used;       // 标记哪些字母已经被用过
string path;             // 当前构建的排列路径
vector<string> res;      // 存放所有排列结果

void dfs(int depth) {
    if (depth == s.size()) {       // 如果已经构建完一整条排列
        res.push_back(path);       // 把结果保存起来
        return;
    }

    for (int i = 0; i < s.size(); ++i) {
        if (!used[i]) {           // 如果这个字母还没被用
            used[i] = true;       // 标记成用过
            path.push_back(s[i]);// 把这个字母加入到当前路径里

            dfs(depth + 1);       // 递归下一位

            path.pop_back();      // 回溯：把这个字母拿出来
            used[i] = false;      // 还原成没用过
        }
    }
}

int main() {
    cin >> s;

    sort(s.begin(), s.end());        // 排序保证按字典序排列
    used = vector<bool>(s.size());   // 初始化 used 数组为 false
    dfs(0);                          // 从第 0 层开始递归

    for (string perm : res) {
        cout << perm << endl;
    }

    return 0;
}
```

---

## 🔎 例子：输入 `"abc"`，程序怎么运行？

* 一开始是 `""`（空）
* 第一位可以选 `a`、`b`、`c`

### 路径一：选 `a` 开头

* 剩下是 `b`、`c`
* 接着选 `b` ⇒ 得到 `a b`

  * 剩下是 `c` ⇒ 得到 `a b c` ✅ 保存
* 回退：把 `b` 拿出来，选 `c` ⇒ 得到 `a c b` ✅ 保存

### 路径二：选 `b` 开头

* 然后 `a`, `c` → 得到 `b a c`、`b c a`

### 路径三：选 `c` 开头

* 然后 `a`, `b` → 得到 `c a b`、`c b a`

最后就得到：

```
abc
acb
bac
bca
cab
cba
```

---

## ✅ 最终你需要记住的逻辑是：

1. 排列 = 所有字符不重复地拼一行
2. 回溯：试一个字母 → 继续拼 → 再回头撤销试别的
3. 用 `used[]` 防止重复用字母
4. 用 `sort()` 先排序，确保从小到大试字母，从而保证**字典序**

---
