我们要解决的问题是：
**在一个 `n × m` 的迷宫中，从左上角走到右下角，找出最少的步数。**
迷宫用 `0` 表示可以走，`1` 表示墙不能走。你可以上下左右四个方向移动。

我们将使用 **广度优先搜索（BFS）**，它可以找到从起点到终点的最短路径。

---

### ✅ C++ 实现 + 每行详细中文注释（符合你所有要求）

```cpp
#include <iostream>           // 输入输出库
#include <queue>             // 队列库，用于BFS广度优先搜索
#include <cstring>           // memset函数库，用于数组初始化
using namespace std;         // 使用标准命名空间，避免写 std::

const int N = 110;           // 地图的最大尺寸，略大于10预留
int maze[N][N];              // 存储迷宫地图，0表示可走，1表示墙
int dist[N][N];              // 存储从起点到当前位置的最短步数

// 定义四个方向的偏移量：上、下、左、右
int dx[4] = {-1, 1, 0, 0};   // 行的变化：上-1，下+1
int dy[4] = {0, 0, -1, 1};   // 列的变化：左-1，右+1

int n, m;                    // n表示行数，m表示列数

// BFS函数：从(0,0)出发，寻找最短路径到(n-1, m-1)
int bfs() {
    queue<pair<int, int>> q;    // 定义一个队列，存储当前可以走的位置
    q.push({0, 0});             // 起点入队

    memset(dist, -1, sizeof dist);  // 初始化距离数组为-1，表示未访问
    dist[0][0] = 0;             // 起点距离为0

    while (!q.empty()) {        // 只要队列不空就继续搜索
        auto t = q.front();     // 取出队首元素
        q.pop();                // 弹出队首

        int x = t.first, y = t.second;  // 当前所在位置

        // 遍历四个方向
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i];          // 新位置的行
            int b = y + dy[i];          // 新位置的列

            // 判断是否越界、是否是墙、是否访问过
            if (a >= 0 && a < n && b >= 0 && b < m && 
                maze[a][b] == 0 && dist[a][b] == -1) {

                dist[a][b] = dist[x][y] + 1;  // 更新距离：当前距离+1
                q.push({a, b});              // 将新位置加入队列
            }
        }
    }

    return dist[n - 1][m - 1];  // 返回终点的最短步数
}

int main() {
    cin >> n >> m;              // 输入行和列

    // 输入迷宫地图
    for (int i = 0; i < n; ++i)     // 遍历每一行
        for (int j = 0; j < m; ++j) // 遍历每一列
            cin >> maze[i][j];      // 读入每个位置的值（0或1）

    cout << bfs() << endl;      // 调用BFS输出结果
    return 0;
}
```

---

### 📌 输入示例

```
5 5
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
```

### ✅ 输出结果

```
8
```

---

### 🧠 思路小结（文字理解）

1. BFS按层级逐步扩展，是最适合找 **最短路径** 的方法。
2. 每走到一个新位置，把它加入队列，并记录走了多少步。
3. 用一个 `dist` 数组来记录从起点到每个位置的最短距离。
4. 只要你没越界、不是墙、没走过，就能继续走。
5. 终点的距离就是答案。

---

这个问题用的是 **广度优先搜索（BFS）** 算法，属于 **图论** 中的基础算法之一，适合用来解决“最短路径”类型的问题。下面我来一步步**用通俗易懂的语言**解释：

---

## 🔍 什么是BFS（Breadth-First Search，广度优先搜索）？

BFS 是一种“**一圈一圈向外扩展**”的搜索方式，就像水从源点向四周扩散一样。
我们每次走的一步，都代表从当前位置出发，走到相邻格子中的某一个。

在迷宫里，BFS 保证：

> 第一次走到终点的位置，所用的步数就是**最短路径**。

---

## 🧠 思想核心

1. **每一个位置，看作一个图中的“点”**；
2. 每个点可以向上下左右四个方向走一步（相邻的格子就是“邻居”）；
3. BFS用**队列**保存当前可以走的点，逐层扩展；
4. 一旦走到终点 `(n-1, m-1)`，就说明走到了，且是最短步数；
5. 用一个 `dist` 数组记录每个点走到的最短路径长度；
6. 所有路径都从 `(0, 0)` 出发，第一次走到终点的路径一定是最短的。

---

## ✅ 本题是如何运作的？

比如这个迷宫：

```
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
```

* 从 `(0,0)` 出发，不能走`1`，只能走 `0`；
* 每次能往上下左右走一步；
* BFS 一层层走，比如先走到所有一步能到的，再走两步能到的，再走三步……

---

## 🏁 结果为什么正确？

因为 **BFS每次走的路径长度是递增的**：

* 第一次走到某点，步数一定是最短的；
* 不再重复走，效率高，不会绕圈子。

---

## 🔗 关联知识

* BFS适合用于“最短路径”、“最少步数”、“最小操作次数”等问题；
* 常见应用：迷宫最短路、图中两点间最短距离、炸弹最小扩散、最短转换路径等。

---

