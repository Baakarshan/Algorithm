
---

## 🔍 **问题简述**

给你一个长度为 `n` 的数列，找出第 `k` 小的数。
例如 `2 4 1 5 3` 中，第 `3` 小的数是 `3`。

---

## ✅ **解题思路：快速选择算法（QuickSelect）**

快速选择是快速排序的变种。它每次只递归“有用的一半”。

### 🧠 基本步骤：

1. 随机选择一个**基准数**（pivot）。
2. 将数组划分为三部分：

   * 小于 pivot 的部分。
   * 等于 pivot 的部分。
   * 大于 pivot 的部分。
3. 判断第 `k` 小的数在哪一部分：

   * 若在左侧，则继续对左侧递归。
   * 若在中间，直接返回 pivot。
   * 若在右侧，则对右侧递归，并更新 k。

---

## ✅ \*\*C++ 代码实现（每行带详细注释）：

```cpp
#include <iostream>
#include <cstdlib>  // rand() 随机函数
using namespace std;

const int N = 1e5 + 10;
int a[N];  // 原始数组

// 快速选择：在 a[l...r] 中找第 k 小的数
int quick_select(int a[], int l, int r, int k) {
    if (l == r) return a[l];  // 区间只剩一个数，直接返回

    // 随机选择一个基准值，并交换到左边
    int pivot_index = rand() % (r - l + 1) + l;
    swap(a[l], a[pivot_index]);

    int pivot = a[l];
    int i = l - 1, j = r + 1;

    // 分区过程：双指针快排分段
    int x = l, y = r;
    while (x < y) {
        while (x < y && a[y] > pivot) y--;
        while (x < y && a[x] <= pivot) x++;
        if (x < y) swap(a[x], a[y]);
    }
    swap(a[l], a[x]);  // 把基准值放回正确位置

    int pos = x - l + 1;  // 计算当前位置是第几个最小的数

    if (k == pos) return a[x];             // 恰好是第 k 小
    else if (k < pos) return quick_select(a, l, x - 1, k);         // 左边找
    else return quick_select(a, x + 1, r, k - pos); // 右边找，k要减去左边数量
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;               // 读入长度和第k小

    for (int i = 0; i < n; ++i)  // 读入数组
        cin >> a[i];

    int res = quick_select(a, 0, n - 1, k); // 快速选择查找第k小
    cout << res << endl;        // 输出结果

    return 0;
}
```

---

## 🔁 示例解释

输入：

```
5 3
2 4 1 5 3
```

目标是找第3小的数。数组排序后是：

```
1 2 3 4 5
```

所以输出：

```
3
```

---
