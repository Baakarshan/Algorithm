#include <vector>    // 引入向量容器头文件，用于存放动态数组
#include <algorithm> // 引入算法头文件，提供常用排序和查找函数
#include <cmath>     // 引入数学函数头文件，提供 floor 等函数
#include <limits>    // 引入极值常量头文件，提供数值类型的最大最小值
using namespace std; // 使用 std 命名空间，省去所有 std:: 前缀

// 冒泡排序（Bubble Sort）：通过相邻元素比较，把最大值逐步“冒泡”到数组末尾
void bubbleSort(vector<int>& a) {
    int n = a.size();                    // 获取数组长度 n
    // 外层循环控制总共需要进行 n-1 趟冒泡
    for (int i = 0; i < n - 1; ++i) {
        // 内层循环依次比较相邻元素，把最大值交换到末端
        for (int j = 0; j < n - i - 1; ++j) {
            // 如果前一个元素大于后一个元素，则交换它们
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]); // 交换操作
        }
    }
}

// 选择排序（Selection Sort）：每次在未排序区间中选出最小元素，放到已排序区末尾
void selectionSort(vector<int>& a) {
    int n = a.size();                    // 获取数组长度 n
    // 从第 0 个位置到第 n-2 个位置，依次选最小元素放到当前位置
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;                   // 假设当前位置 i 存储的元素是当前未排序区的最小值
        // 在 i+1 到 n-1 范围内寻找真正的最小元素下标
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIdx]) minIdx = j; // 更新最小值索引
        }
        // 如果找到了比当前位置更小的元素，则交换
        if (minIdx != i) swap(a[i], a[minIdx]); // 交换操作
    }
}

// 插入排序（Insertion Sort）：把每个元素插入到它之前已经排好序的部分
void insertionSort(vector<int>& a) {
    int n = a.size();                    // 获取数组长度 n
    // 从下标 1 开始，依次将每个元素插入到它之前的有序区间中
    for (int i = 1; i < n; ++i) {
        int key = a[i];                  // key 是当前待插入的元素值
        int j = i - 1;                   // j 是有序区间末尾的下标
        // 将所有大于 key 的元素后移一位，为插入 key 腾位置
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];             // 元素后移
            --j;                         // 继续向左扫描
        }
        a[j + 1] = key;                  // 将 key 插入到正确位置
    }
}

// 归并函数：将两个有序子数组 [l..m] 和 [m+1..r] 合并成一个有序数组
void merge(vector<int>& a, int l, int m, int r) {
    int n1 = m - l + 1;                // 左半区长度
    int n2 = r - m;                    // 右半区长度
    // 创建临时数组 L 和 R，保存左右两半数据
    vector<int> L(a.begin() + l, a.begin() + m + 1);
    vector<int> R(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = l;           // 分别是 L、R、a 的当前下标
    // 依次比较两个子数组的当前元素，把较小的放回原数组
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++]; // L 的当前元素较小或相等
        else             a[k++] = R[j++]; // R 的当前元素较小
    }
    // 如果 L 还有剩余元素，全部拷贝回来
    while (i < n1) a[k++] = L[i++];
    // 如果 R 还有剩余元素，全部拷贝回来
    while (j < n2) a[k++] = R[j++];
}

// 归并排序（Merge Sort）：分治策略，递归拆分再合并
void mergeSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;       // 计算拆分点 m
        mergeSort(a, l, m);            // 递归排序左半区
        mergeSort(a, m + 1, r);        // 递归排序右半区
        merge(a, l, m, r);             // 合并两个有序半区
    }
}

// 划分函数：快速排序中用于分区，使得基准左侧小于它，右侧大于它
int partition(vector<int>& a, int l, int r) {
    int pivot = a[r];                 // 选择最后一个元素作为基准
    int i = l - 1;                    // i 用于标记小于区的末尾
    // 遍历 [l..r-1]，把小于基准的元素交换到小于区末尾
    for (int j = l; j < r; ++j) {
        if (a[j] < pivot) swap(a[++i], a[j]); // 扩大小于区
    }
    swap(a[i + 1], a[r]);             // 把基准交换到中间位置
    return i + 1;                     // 返回基准最终位置
}

// 快速排序（Quick Sort）：分而治之，平均 O(n log n)
void quickSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int pi = partition(a, l, r); // 划分获取基准位置
        quickSort(a, l, pi - 1);      // 排序基准左侧
        quickSort(a, pi + 1, r);      // 排序基准右侧
    }
}

// 堆调整：维护以 i 为根的子树为大顶堆
void heapify(vector<int>& a, int n, int i) {
    int largest = i;                  // 假设根节点最大
    int l = 2*i + 1;                  // 左子节点下标
    int r = 2*i + 2;                  // 右子节点下标
    // 比较左子节点
    if (l < n && a[l] > a[largest]) largest = l;
    // 比较右子节点
    if (r < n && a[r] > a[largest]) largest = r;
    // 如果最大元素不是根节点，则交换并递归调整
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

// 堆排序（Heap Sort）：先建堆，再不停交换堆顶与末尾
void heapSort(vector<int>& a) {
    int n = a.size();                // 数组长度
    // 建立初始大顶堆，从最底层非叶节点开始
    for (int i = n/2 - 1; i >= 0; --i) heapify(a, n, i);
    // 逐步把堆顶最大值放到末尾，然后重新 heapify
    for (int i = n - 1; i > 0; --i) {
        swap(a[0], a[i]);            // 堆顶与末尾交换
        heapify(a, i, 0);            // 调整剩余元素为堆
    }
}

// 计数排序（Counting Sort）：适用于非负整数，通过频次统计重建
void countingSort(vector<int>& a) {
    if (a.empty()) return;          // 空数组直接返回
    int M = *max_element(a.begin(), a.end()); // 找出最大元素
    vector<int> cnt(M + 1, 0);       // 频次数组
    for (int x : a) ++cnt[x];        // 统计每个值出现次数
    int idx = 0;                     // 重建时的写入下标
    for (int v = 0; v <= M; ++v) {   // 遍历所有可能的值
        while (cnt[v]-- > 0) a[idx++] = v; // 按次数写回原数组
    }
}

// 桶排序（Bucket Sort）：适用于 [0,1) 区间浮点数，分桶后排序合并
void bucketSort(vector<double>& a) {
    int n = a.size(); if (n == 0) return;           // 空数组直接返回
    vector<vector<double>> B(n);                     // 建立 n 个桶
    for (double x : a) {                             // 将每个元素放入对应桶
        int i = floor(x * n);                       // 计算桶索引
        if (i == n) i = n - 1;                      // 边界值处理
        B[i].push_back(x);
    }
    for (auto& b : B) sort(b.begin(), b.end());     // 对每个桶内部排序
    int idx = 0;                                     // 写回原数组
    for (auto& b : B) for (double x : b) a[idx++] = x;
}

// 基数排序（Radix Sort）：对十进制整数，从最低位到最高位逐位稳定排序
void radixSort(vector<int>& a) {
    if (a.empty()) return;                          // 空数组直接返回
    int M = *max_element(a.begin(), a.end());       // 找到最大值
    // 从个位开始，对每一位执行计数排序
    for (int exp = 1; M / exp > 0; exp *= 10) {
        vector<int> cnt(10, 0), out(a.size());       // 10 个计数，输出数组
        for (int x : a) ++cnt[(x / exp) % 10];       // 统计该位数字
        for (int i = 1; i < 10; ++i) cnt[i] += cnt[i - 1]; // 前缀和
        for (int i = (int)a.size() - 1; i >= 0; --i) {      // 从后向前保持稳定
            int d = (a[i] / exp) % 10;
            out[--cnt[d]] = a[i];                   // 写入输出
        }
        a = out;                                    // 复制回原数组
    }
}

/* 示例用法：
int main() {
    vector<int> v = {5, 2, 9, 1, 5, 6};
    quickSort(v, 0, v.size() - 1);  // 调用快速排序示例
    return 0;
}
*/
