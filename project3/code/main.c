#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define Max_Nv 1000
#define Max_Ne 100000
#define Max_K 100
#define Max_Cost 100

typedef struct Node Node;
typedef struct Edge Edge;
typedef struct MinHeap MinHeap;

struct Node{
    int distance;
    bool visited;
    int before;
    Edge* edges;
};

struct Edge{
    int data;
    int cost;
    struct Edge* next;
};

struct MinHeap{
    int size;
    int* indexes;
};



Node* CreatEdges(Node* nodes,int Nv,int Ne);//Creat all edges and link them to the nodes in the graph.

Node* FreeNodes(Node* nodes,int Nv);

Node* Initial(Node* nodes,MinHeap* minHeap,int Nv);

MinHeap* PercolateUp(MinHeap* minHeap,int Nv,int index);

MinHeap* PercolateDown(MinHeap* minHeap,int Nv,int index);

int main(){
    int Nv, Ne;
    scanf("%d %d",&Nv,&Ne);
    if(Nv>Max_Nv || Nv<1 || Ne>Max_Ne || Ne<1){
        printf("Invalid input\n");
        return 0;
    }
    Node* nodes=(Node*)malloc(sizeof(Node)*(Nv+1));
    if(nodes==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }
    nodes=CreatEdges(nodes,Nv,Ne);
    if(nodes==NULL)return 0;
    MinHeap* minHeap=(MinHeap*)malloc(sizeof(MinHeap));
    if(minHeap==NULL){
        printf("Memory allocation failed\n");
        FreeNodes(nodes,Nv);
        return 0;
    }
    minHeap->size=0;
    minHeap->indexes=(int*)malloc(sizeof(int)*(Nv+1));


    return 0;
}

Node* CreatEdges(Node* nodes,int Nv,int Ne){
    int a,b,cost;
    memset(nodes,0,sizeof(Node)*(Nv+1));
        for(int i=1;i<=Ne;i++){
        int temp=scanf("%d %d %d",&a,&b,&cost);
        if(a>Nv || a<1 || b>Nv || b<1 || cost<0 || cost>Max_Cost || temp!=3){
            printf("Invalid input\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        Edge* a_NewEdge=(Edge*)malloc(sizeof(Edge));
        if(a_NewEdge==NULL){
            printf("Memory allocation failed\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        a_NewEdge->data=b;
        a_NewEdge->cost=cost;
        a_NewEdge->next=NULL;
        Edge* b_NewEdge=(Edge*)malloc(sizeof(Edge));
        if(b_NewEdge==NULL){
            printf("Memory allocation failed\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        b_NewEdge->data=a;
        b_NewEdge->cost=cost;
        b_NewEdge->next=NULL;
        Edge* current=nodes[a].edges;
        while(current!=NULL){
            current=current->next;
        }
        current->next=a_NewEdge;
        current=nodes[b].edges;
        while(current!=NULL){
            current=current->next;
        }
        current->next=b_NewEdge;
    }
    return nodes;
}

Node* FreeNodes(Node* nodes,int Nv){
    for(int i=1;i<=Nv;i++){
        Edge* current=nodes[i].edges;
        while(current!=NULL){
            Edge* temp=current;
            current=current->next;
            free(temp);
        }
    }
    free(nodes);
    return NULL;
}

Node* Initial(Node* nodes,MinHeap* MinHeap,int Nv){
    for(int i=1;i<=Nv;i++){
        nodes[i].distance=Max_Cost*Max_Nv+1;
        nodes[i].before=0;
        nodes[i].visited=false;
    }
    memset(MinHeap->indexes,0,sizeof(int)*(Nv+1));
    MinHeap->size=0;
    return nodes;
}