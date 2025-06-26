要求从一个数组中找出**前 `k` 大的数**，并按照从大到小的顺序输出。

---

### ✅ 思路解析（优先队列/小根堆）

我们可以用 **小根堆（priority\_queue）** 来解决这个问题：

* **为什么小根堆？**

  * 小根堆顶是当前最小的元素，堆大小保持为 `k`。
  * 扫描数组时，如果新元素比堆顶大，就替换堆顶，这样堆中始终保留的是**前 `k` 大的数**。

* **最后怎么输出？**

  * 把堆中的 `k` 个数取出，存入数组，排序逆序输出即可。

---

### ✅ C++ 代码（带详细注释）

```cpp
#include <iostream>          // 引入输入输出库，用于使用 cin、cout
#include <queue>            // 引入队列库，用于使用 priority_queue（优先队列）
#include <vector>           // 引入向量库，用于使用 vector 动态数组
#include <algorithm>        // 引入算法库，用于使用 sort 排序函数
using namespace std;        // 使用标准命名空间，避免每次都写 std::

int main() {
    int n;
    cin >> n;               // 读取一个整数 n，表示数组的元素个数

    vector<int> a(n);       // 创建一个长度为 n 的动态数组（vector），用于存储输入的数
    for (int i = 0; i < n; ++i)
        cin >> a[i];        // 逐个读取数组中的每个整数，存入 a 中

    int k;
    cin >> k;               // 读取一个整数 k，表示需要找出前 k 个最大的数

    // 创建一个小根堆（最小堆），默认 priority_queue 是大根堆
    // 使用 greater<int> 表示优先级小的元素排在前面，即堆顶是最小值
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // 先把数组前 k 个元素放入堆中，作为初始的候选最大值集合
    for (int i = 0; i < k; ++i) {
        minHeap.push(a[i]); // 把第 i 个元素压入堆中
    }

    // 遍历数组剩余的元素（从第 k 个到第 n-1 个）
    for (int i = k; i < n; ++i) {
        // 如果当前元素比堆顶元素还大，说明它有资格进入前 k 大集合
        if (a[i] > minHeap.top()) {
            minHeap.pop();          // 弹出堆顶最小的元素（因为它不再是前 k 大了）
            minHeap.push(a[i]);     // 把当前更大的元素加入堆中
        }
    }

    // 创建一个结果数组，用于保存堆中的前 k 大数
    vector<int> result;
    while (!minHeap.empty()) {          // 当堆非空时，持续取出元素
        result.push_back(minHeap.top()); // 将堆顶元素添加到结果数组中
        minHeap.pop();                   // 移除堆顶元素
    }

    // 将结果数组排序，从大到小排序
    // rbegin() 和 rend() 是反向迭代器，用于降序排列
    sort(result.rbegin(), result.rend());

    // 逐行输出前 k 大的元素（已经是从大到小的顺序）
    for (int num : result)
        cout << num << endl;

    return 0;  // 返回 0 表示程序正常结束
}

```

---

### ✅ 输入样例

```
10
4 5 6 9 8 7 1 2 3 0
5
```

### ✅ 输出样例

```
9
8
7
6
5
```

---


