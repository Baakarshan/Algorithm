
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
#include <iostream>     // 输入输出头文件
#include <cstdlib>      // 提供 rand() 函数用于随机数生成
using namespace std;

// 定义数组最大长度为 1e5 + 10，防止越界
const int N = 1e5 + 10;
int a[N];  // 原始数组，用于存储输入的 n 个数

// 快速选择函数：在数组 a 的下标区间 [l, r] 中找出第 k 小的元素
int quick_select(int a[], int l, int r, int k) {
    if (l == r) return a[l];  // 如果当前区间只有一个元素，那就是第 k 小的，直接返回

    // 随机选择一个 pivot（基准数）的下标，避免最坏情况，提高期望性能
    int pivot_index = rand() % (r - l + 1) + l;
    swap(a[l], a[pivot_index]); // 将基准数换到左端，方便分区处理

    int pivot = a[l];         // 记录基准值
    int i = l - 1, j = r + 1; // 初始化双指针（不用于下面的实现，写冗余了）

    // 开始分区：使用快排中的双指针思想，将比 pivot 小的放左边，大的放右边
    int x = l, y = r;
    while (x < y) {
        // 从右往左找第一个小于等于 pivot 的数
        while (x < y && a[y] > pivot) y--;
        // 从左往右找第一个大于 pivot 的数
        while (x < y && a[x] <= pivot) x++;
        // 如果还没相遇，就交换它们，确保 pivot 左边都是小于等于它的数
        if (x < y) swap(a[x], a[y]);
    }

    // 把 pivot 放回它应该在的位置（即 x 所在的位置）
    swap(a[l], a[x]);

    // pos 表示 pivot 是当前区间中第几个最小的数（从 l 开始计数）
    int pos = x - l + 1;

    if (k == pos)
        return a[x];  // 找到第 k 小的数，直接返回
    else if (k < pos)
        return quick_select(a, l, x - 1, k);  // 递归到左半区间去找第 k 小
    else
        return quick_select(a, x + 1, r, k - pos);  // 递归右半区间找剩下的第 (k - pos) 小
}

// 主函数入口
int main() {
    ios::sync_with_stdio(false);  // 禁用同步，提高 cin/cout 的读写效率
    cin.tie(nullptr);             // 解绑 cin 和 cout，提高效率

    int n, k;      // n 表示数组长度，k 表示要找第 k 小的数
    cin >> n >> k; // 读入 n 和 k

    // 输入数组的 n 个元素
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // 使用快速选择算法找第 k 小的数
    int res = quick_select(a, 0, n - 1, k);

    // 输出答案
    cout << res << endl;

    return 0; // 程序结束
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
