#include <stdio.h>  
#include <stdlib.h>

struct Node{
    int data;
    int count;
    struct Node* next;
};

struct List{
    struct Node* head;
    int size;
    int num;
};

struct search{
    struct Node* local;
};

void add(struct List* list1, struct List* list2, int data, int K, int N, struct search search[20000]) {
    (void)search;  // 按你的要求不改其它结构，这里不使用 search

    // 题面页号范围 [1, 20000]
    // where: 0-不在队列, 1-在历史队列, 2-在缓存队列
    static unsigned char where[20001] = {0};
    static struct Node* nodeOf[20001] = {0};
    static struct Node* prevOf[20001] = {0};

    // 两个单链表的尾指针，首次调用时初始化
    static int inited = 0;
    static struct Node* tail1 = NULL; // history tail
    static struct Node* tail2 = NULL; // cache tail
    if (!inited) {
        tail1 = list1->head;
        tail2 = list2->head;
        inited = 1;
    }

    if (data < 1 || data > 20000) return;

    // O(1) 把节点从所属队列摘下
    #define REMOVE_FROM_LIST(_list, _tail, _id, _x)            \
        do {                                                   \
            struct Node* _p = prevOf[_id];                    \
            struct Node* _n = (_x)->next;                     \
            _p->next = _n;                                    \
            if (_n) prevOf[_n->data] = _p;                    \
            else (_tail) = _p;                                \
            (_list)->size--;                                  \
        } while (0)

    // O(1) 尾插到所属队列
    #define APPEND_TO_LIST(_list, _tail, _id, _x)             \
        do {                                                   \
            (_tail)->next = (_x);                             \
            prevOf[_id] = (_tail);                            \
            (_tail) = (_x);                                   \
            (_x)->next = NULL;                                \
            (_list)->size++;                                  \
        } while (0)

    // O(1) 淘汰队首
    #define EVICT_FRONT(_list, _tail)                         \
        do {                                                   \
            struct Node* _ev = (_list)->head->next;           \
            int _vid = _ev->data;                             \
            struct Node* _nn = _ev->next;                     \
            (_list)->head->next = _nn;                        \
            if (_nn) prevOf[_nn->data] = (_list)->head;       \
            else (_tail) = (_list)->head;                     \
            (_list)->size--;                                  \
            where[_vid] = 0;                                  \
            nodeOf[_vid] = NULL;                              \
            prevOf[_vid] = NULL;                              \
            free(_ev);                                        \
        } while (0)

    struct Node* x = nodeOf[data];

    // 1) 在缓存队列：命中后移到队尾
    if (where[data] == 2) {
        x->count++;
        if (x != tail2) {
            REMOVE_FROM_LIST(list2, tail2, data, x);
            APPEND_TO_LIST(list2, tail2, data, x);
        }
        return;
    }

    // 2) 在历史队列：命中次数+1；达到 K 次则晋升缓存
    if (where[data] == 1) {
        x->count++;
        if (x->count >= K) {
            REMOVE_FROM_LIST(list1, tail1, data, x);
            APPEND_TO_LIST(list2, tail2, data, x);
            where[data] = 2;

            if (list2->size > N) {
                EVICT_FRONT(list2, tail2);
            }
        } else {
            if (x != tail1) {
                REMOVE_FROM_LIST(list1, tail1, data, x);
                APPEND_TO_LIST(list1, tail1, data, x);
            }
        }
        return;
    }

    // 3) 新页
    x = (struct Node*)malloc(sizeof(struct Node));
    x->data = data;
    x->count = 1;
    x->next = NULL;
    nodeOf[data] = x;

    // K==1 时首次访问直接进入缓存（LRU-1）
    if (K <= 1) {
        APPEND_TO_LIST(list2, tail2, data, x);
        where[data] = 2;
        if (list2->size > N) {
            EVICT_FRONT(list2, tail2);
        }
    } else {
        APPEND_TO_LIST(list1, tail1, data, x);
        where[data] = 1;
        if (list1->size > N) {
            EVICT_FRONT(list1, tail1);
        }
    }

    #undef REMOVE_FROM_LIST
    #undef APPEND_TO_LIST
    #undef EVICT_FRONT
}

void printList(struct List* list){
    if(list->size == 0){
        printf("-\n");
        return;
    }
    struct Node* current = list->head->next;
    while(current->next!= NULL){
        printf("%d ",current->data);
        current = current->next;
    }
    printf("%d\n",current->data);
}

int main() {
    int K=0,N=0,M=0;
    struct search search[20000]={0,NULL};
    struct List list1,list2;
    list1.head = (struct Node*)malloc(sizeof(struct Node));
    list1.head->data = -1;
    list1.head->count = -1;
    list1.head->next = NULL;
    list1.size = 0;
    list1.num = 1;
    list2.head = (struct Node*)malloc(sizeof(struct Node));
    list2.head->data = -1;
    list2.head->count = -1;
    list2.head->next = NULL;
    list2.size = 0;
    list2.num = 2;
    scanf("%d %d %d",&K,&N,&M);
    for(int i=0;i<M;i++){
        int data;
        scanf("%d",&data);
        add(&list1,&list2,data,K,N,search);
    }
    printList(&list1);
    printList(&list2);
    return 0;

}