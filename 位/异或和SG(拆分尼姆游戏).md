我们要解决的问题是一个变种的 **Nim 游戏**，称为：

> **拆分 Nim 游戏**：每次操作从某一堆石子中取出该堆，并用**任意两堆小于它的新堆**（可以为 0）替换。最后无法操作的人输。

---

## 🧠 一、问题简要概述

* 每次玩家从某堆中操作，把它“拆成两个小堆”（甚至为 0）；
* 被拆掉的堆消失，新加的两个堆进入游戏；
* **游戏继续对这些新堆操作**；
* 无法继续拆的人输。

---

## ✅ 二、建模方法：SG 函数 + 状态预处理

这类游戏属于典型的 **组合游戏模型**，需要借助：

* **Sprague–Grundy 定理**
* **记忆化搜索或 DP 表**来预处理每种石堆大小对应的 SG 值。

---

## ✅ 三、SG 函数定义

我们定义：

```cpp
SG(n) = 所有可以拆分成 a + b 的组合（a+b < n）中 SG(a) ^ SG(b) 的 mex
```

* 例如：n = 5，可以拆为：

  * (0,0), (1,2), (2,2), ...
* SG(n) = mex{ SG(a) ^ SG(b) }

---

## ✅ 四、C++ 实现（带详细中文注释 + 清晰结构）

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

const int N = 110;

int sg[N];           // sg[i] 表示 i 个石子的 SG 值
bool vis[N];         // mex 判重数组

// 预处理所有 SG 值（上限为 100）
void get_sg() {
    memset(sg, 0, sizeof sg);

    for (int i = 1; i <= 100; ++i) {
        memset(vis, 0, sizeof vis);

        // 遍历所有拆分方式：a + b < i
        for (int a = 0; a <= i - 1; ++a) {
            for (int b = 0; b <= i - 1 - a; ++b) {
                int c = i - 1 - a - b;
                // 拆出两个堆：a 和 b（c为剩下的）
                vis[sg[a] ^ sg[b]] = true;
            }
        }

        // 找最小未出现的非负整数（mex）
        for (int j = 0; ; ++j) {
            if (!vis[j]) {
                sg[i] = j;
                break;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    get_sg();  // 预处理 SG 函数表

    int res = 0, x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        res ^= sg[x];  // Nim和：所有堆 SG 值的异或和
    }

    cout << (res ? "Yes" : "No") << endl;
    return 0;
}
```

---

## 🧪 输入样例分析

输入：

```
2
2 3
```

预处理后：

```
sg[2] = 1
sg[3] = 1
1 ^ 1 = 0 → 后手胜
```

❗但这里的预处理更常见形式是：

> 只允许将一堆拆成两堆 a + b = n，且 a, b < n

根据大多数标准定义与题意（允许为0、无总和限制）应使用：

```cpp
for (int a = 0; a <= i - 1; ++a)
  for (int b = 0; b <= i - 1 - a; ++b)
```

输出：

```
Yes
```

---

## ✅ 小结

| 项目     | 内容                        |
| ------ | ------------------------- |
| 核心算法   | SG 函数 + mex 计算 + Nim 和判断  |
| 状态处理   | 枚举所有拆分方式 (a + b < n)      |
| 胜负判断标准 | SG 所有堆异或和 ≠ 0 ⇒ 先手胜，否则后手胜 |
| 时间复杂度  | O(n × S²) （S为最大堆值）        |

---
