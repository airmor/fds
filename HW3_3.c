#include <stdio.h>  // 标准输入输出头文件
#include <stdlib.h> // 标准库头文件，包含malloc、free等函数

// 定义节点结构体，用于堆排序
typedef struct {
    int value;   // 节点的值
    int frozen;  // 冻结标志：0表示当前运行，1表示下一个运行
} Node;

// 比较两个节点的大小，用于堆排序
static int node_less(const Node *a, const Node *b) {
    // 首先比较冻结标志，冻结标志小的优先级高
    if (a->frozen != b->frozen) return a->frozen < b->frozen;
    // 冻结标志相同则比较值的大小
    return a->value < b->value;
}

// 堆的上浮操作（将节点向上移动以维持堆性质）
static void heap_sift_up(Node *heap, int idx) {
    while (idx > 0) {  // 当节点不是根节点时继续
        int p = (idx - 1) >> 1;  // 计算父节点索引（使用位运算代替除以2）
        // 如果当前节点不小于父节点，则堆性质已满足，退出循环
        if (!node_less(&heap[idx], &heap[p])) break;
        // 交换当前节点和父节点
        Node t = heap[idx];
        heap[idx] = heap[p];
        heap[p] = t;
        idx = p;  // 更新当前节点索引为父节点位置
    }
}

// 堆的下沉操作（将节点向下移动以维持堆性质）
static void heap_sift_down(Node *heap, int size, int idx) {
    while (1) {
        int l = idx * 2 + 1;  // 左子节点索引
        int r = l + 1;        // 右子节点索引
        int best = idx;       // 假设当前节点是最小的

        // 如果左子节点存在且比当前节点小，则更新最小节点为左子节点
        if (l < size && node_less(&heap[l], &heap[best])) best = l;
        // 如果右子节点存在且比当前节点小，则更新最小节点为右子节点
        if (r < size && node_less(&heap[r], &heap[best])) best = r;
        // 如果当前节点已经是最小的，则堆性质已满足，退出循环
        if (best == idx) break;

        // 交换当前节点和最小子节点
        Node t = heap[idx];
        heap[idx] = heap[best];
        heap[best] = t;
        idx = best;  // 更新当前节点索引为子节点位置
    }
}

// 构建堆（将数组转换为最小堆）
static void heap_build(Node *heap, int size) {
    // 从最后一个非叶子节点开始，向前遍历所有节点
    for (int i = (size - 2) / 2; i >= 0; --i) {
        heap_sift_down(heap, size, i);  // 对每个节点执行下沉操作
    }
}

// 向堆中插入新节点
static void heap_push(Node *heap, int *size, Node x) {
    heap[*size] = x;      // 将新节点放在堆的末尾
    (*size)++;            // 堆大小加1
    heap_sift_up(heap, (*size) - 1);  // 对新节点执行上浮操作
}

// 从堆中弹出最小节点
static Node heap_pop(Node *heap, int *size) {
    Node ret = heap[0];   // 堆顶节点是最小值
    (*size)--;            // 堆大小减1
    if (*size > 0) {      // 如果堆中还有元素
        heap[0] = heap[*size];  // 将最后一个元素移到堆顶
        heap_sift_down(heap, *size, 0);  // 对堆顶执行下沉操作
    }
    return ret;  // 返回弹出的最小节点
}

// 主函数
int main(void) {
    int N, M;  // N: 总记录数，M: 内存中可容纳的记录数

    // 循环读取多组测试数据
    while (scanf("%d %d", &N, &M) == 2) {
        // 分配堆内存，大小为M个Node
        Node *heap = (Node *)malloc((size_t)M * sizeof(Node));
        if (!heap) return 0;  // 内存分配失败则退出

        // 读取前M个记录到堆中
        for (int i = 0; i < M; ++i) {
            scanf("%d", &heap[i].value);  // 读取值
            heap[i].frozen = 0;           // 初始化为当前运行（未冻结）
        }

        int heap_size = M;        // 当前堆大小
        int remaining = N - M;    // 剩余待处理的记录数
        int line_first = 1;       // 标记是否为当前行的第一个输出
        int last_output = 0;      // 上一个输出的值

        heap_build(heap, heap_size);  // 构建初始堆

        // 当堆不为空时继续处理
        while (heap_size > 0) {
            // 如果堆顶节点属于下一个运行（冻结标志为1）
            if (heap[0].frozen == 1) {
                putchar('\n');  // 输出换行符，开始新的一行
                // 将所有节点的冻结标志重置为0（当前运行）
                for (int i = 0; i < heap_size; ++i) heap[i].frozen = 0;
                heap_build(heap, heap_size);  // 重新构建堆
                line_first = 1;  // 标记为新行的第一个输出
            }

            // 从堆中弹出最小节点
            Node out = heap_pop(heap, &heap_size);

            // 如果不是当前行的第一个输出，先输出空格
            if (!line_first) putchar(' ');
            printf("%d", out.value);  // 输出节点的值
            line_first = 0;           // 标记已输出过
            last_output = out.value;  // 更新上一个输出的值

            // 如果还有剩余记录需要处理
            if (remaining > 0) {
                int x;
                scanf("%d", &x);  // 读取下一个记录
                Node in;
                in.value = x;
                // 如果新记录小于上一个输出，则属于下一个运行（冻结标志为1）
                in.frozen = (x < last_output) ? 1 : 0;
                heap_push(heap, &heap_size, in);  // 将新记录插入堆中
                remaining--;  // 剩余记录数减1
            }
        }

        putchar('\n');  // 输出最后的换行符
        free(heap);     // 释放堆内存
    }

    return 0;  // 程序正常结束
}