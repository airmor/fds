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
    int data;
    int num;
    struct Node* local;
};

void add(struct List* list1,struct List* list2, int data,int K,int N){
    struct Node* current = list2->head;
    while(current->next!= NULL){
        if(current->next->data == data){
            current->next->count++;
            struct Node* temp = current->next;
            current->next = temp->next;
            temp->next = NULL;
            while(current->next!= NULL){
                current = current->next;
            }
            current->next = temp;
            return;
        }
        current = current->next;
    }
    current = list1->head;
    while(current->next!= NULL){
        if(current->next->data == data){
            current->next->count++;
            if(current->next->count == K){
                struct Node* temp = current->next;
                current->next = temp->next;
                list1->size--;
                current = list2->head;
                while(current->next!= NULL){
                    current = current->next;
                }
                current->next = temp;
                temp->next = NULL;
                list2->size++;
                if(list2->size > N){
                    struct Node* temp2 = list2->head->next;
                    list2->head->next = temp2->next;
                    free(temp2);
                    list2->size--;
                }
            }else{
                struct Node* temp = current->next;
                current->next = temp->next;
                temp->next = NULL;
                while(current->next!= NULL){
                    current = current->next;
                }
                current->next = temp;
            }
            return;
        }
        current = current->next;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->count = 1;
    newNode->next = NULL;
    current->next = newNode;
    list1->size++;
    if(current->next->count == K){
                struct Node* temp = current->next;
                current->next = temp->next;
                list1->size--;
                current = list2->head;
                while(current->next!= NULL){
                    current = current->next;
                }
                current->next = temp;
                temp->next = NULL;
                list2->size++;
                if(list2->size > N){
                    struct Node* temp2 = list2->head->next;
                    list2->head->next = temp2->next;
                    free(temp2);
                    list2->size--;
                }
            }
    if(list1->size > N){
        struct Node* temp = list1->head->next;
        list1->head->next = temp->next;
        free(temp);
        list1->size--;
    }
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
        add(&list1,&list2,data,K,N);
    }
    printList(&list1);
    printList(&list2);
    return 0;

}