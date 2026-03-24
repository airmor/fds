#include <stdio.h>  
#include <stdlib.h>

struct Node{
    int data;
    int count;
    struct Node* next;
    struct Node* prev;
};

struct List{
    struct Node* head;
    struct Node* tail;
    int size;
    int num;
};

struct search{
    struct Node* local;
};

void add(struct List* list1, struct List* list2, int data, int K, int N, struct search search[20000]) {
    if (K <= 1){
    if (search[data].local == NULL){
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->count = 1;
        search[data].local = newNode;

        newNode->next = list2->head->next;
        newNode->prev = list2->head;
        list2->head->next->prev = newNode;
        list2->head->next = newNode;
        list2->size++;

        if (list2->size > N){
            struct Node *victim = list2->tail->prev;
            if (victim != list2->head){
                int victimData = victim->data;
                victim->prev->next = list2->tail;
                list2->tail->prev = victim->prev;
                search[victimData].local = NULL;
                free(victim);
                list2->size--;
            }
        }
    } else {
        struct Node* node = search[data].local;
        node->count++;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = list2->head->next;
        node->prev = list2->head;
        list2->head->next->prev = node;
        list2->head->next = node;
    }
    return;
}
    if(search[data].local != NULL){
        if(search[data].local->count < K-1){
            search[data].local->count++;
            search[data].local->prev->next = search[data].local->next;
            search[data].local->next->prev = search[data].local->prev;
            search[data].local->next = list1->head->next;
            search[data].local->prev = list1->head;
            list1->head->next->prev = search[data].local;
            list1->head->next = search[data].local;
        }
        else if(search[data].local->count == K-1){
            search[data].local->count++;
            list1->size--;
            search[data].local->prev->next = search[data].local->next;
            search[data].local->next->prev = search[data].local->prev;
            search[data].local->next = list2->head->next;
            search[data].local->prev = list2->head;
            list2->head->next->prev = search[data].local;
            list2->head->next = search[data].local;
            list2->size++;
            if (list2->size > N) {
                struct Node *victim = list2->tail->prev;
                if (victim != list2->head) {
                    int victimData = victim->data;
                    victim->prev->next = list2->tail;
                    list2->tail->prev = victim->prev;
                    search[victimData].local = NULL;
                    free(victim);
                    list2->size--;
                }
            }
        }
        else{
            search[data].local->count++;
            search[data].local->prev->next = search[data].local->next;
            search[data].local->next->prev = search[data].local->prev;
            search[data].local->next = list2->head->next;
            search[data].local->prev = list2->head;
            list2->head->next->prev = search[data].local;
            list2->head->next = search[data].local;
        }
    }
    else{
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->count = 1;
        newNode->next = NULL;
        search[data].local = newNode;
        if(list1->size < N){
            newNode->next = list1->head->next;
            newNode->prev = list1->head;
            list1->head->next->prev = newNode;
            list1->head->next = newNode;
            list1->size++;
        }
        else{
            newNode->next = list1->head->next;
            newNode->prev = list1->head;
            list1->head->next->prev = newNode;
            list1->head->next = newNode;
            struct Node *victim = list1->tail->prev;
            if (victim != list1->head) {
                int victimData = victim->data;
                victim->prev->next = list1->tail;
                list1->tail->prev = victim->prev;
                search[victimData].local = NULL;
                free(victim);
            }
        }
    }
}


void printList(struct List* list){
    if(list->size == 0||list->head->next == list->tail){
        printf("-\n");
        return;
    }
    struct Node* current = list->tail->prev;
    while(current->prev != list->head){
        printf("%d ",current->data);
        current = current->prev;
    }
    printf("%d\n",current->data);
}

int main() {
    int K=0,N=0,M=0;
    struct search search[20001]={0};
    struct List list1,list2;
    list1.head = (struct Node*)malloc(sizeof(struct Node));
    list1.head->data = -1;
    list1.head->count = -1;
    list1.head->next = NULL;
    list1.head->prev = NULL;
    list1.size = 0;
    list1.num = 1;
    list1.tail = (struct Node*)malloc(sizeof(struct Node));
    list1.tail->data = -1;
    list1.tail->count = -1;
    list1.tail->next = NULL;
    list1.tail->prev = NULL;
    list1.head->next = list1.tail;
    list1.tail->prev = list1.head;
    list2.head = (struct Node*)malloc(sizeof(struct Node));
    list2.head->data = -1;
    list2.head->count = -1;
    list2.head->next = NULL;
    list2.head->prev = NULL;
    list2.size = 0;
    list2.num = 2;
    list2.tail = (struct Node*)malloc(sizeof(struct Node));
    list2.tail->data = -1;
    list2.tail->count = -1;
    list2.tail->next = NULL;
    list2.tail->prev = NULL;
    list2.head->next = list2.tail;
    list2.tail->prev = list2.head;
    scanf("%d %d %d",&K,&N,&M);
    for(int i=0;i<M;i++){
        int data;
        scanf("%d", &data);
        add(&list1,&list2,data,K,N,search);
    }
    printList(&list1);
    printList(&list2);
    return 0;

}