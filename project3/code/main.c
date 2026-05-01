// Standard headers used for input, output, allocation, and memset.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use int as a lightweight boolean type.
#define bool int
#define true 1
#define false 0

// Problem constraints.
#define Max_Nv 1000
#define Max_Ne 100000
#define Max_K 100
#define Max_Cost 100

// Forward declarations for the graph and heap structures.
typedef struct Node Node;
typedef struct Edge Edge;
typedef struct MinHeap MinHeap;

// Each vertex stores the current tentative distance, visit state,
// predecessor, heap index, and adjacency list head.
struct Node{
    int distance;   // Current shortest distance estimate
    bool visited;   // Whether this vertex has been discovered
    int before;     // Previous vertex in the path
    int index;      // Position in the min-heap
    Edge* edges;    // Adjacency list head node
};

// Each edge stores the adjacent vertex, its cost, and the next edge.
struct Edge{
    int data;          // Adjacent vertex id
    int cost;          // Edge weight
    struct Edge* next;  // Next edge in the adjacency list
};

// Min-heap of vertex ids used to simulate Dijkstra's frontier.
struct MinHeap{
    int size;      // Number of valid elements in the heap
    int* indexes;  // Vertex ids arranged by heap order
};



// Build all edges and link them into the adjacency lists.
Node* CreatEdges(Node* nodes,int Nv,int Ne);

// Free the adjacency lists and the vertex array.
Node* FreeNodes(Node* nodes,int Nv);

// Reset vertex and heap state before checking one query sequence.
Node* Initial(Node* nodes,MinHeap* minHeap,int Nv);

// Restore the min-heap property by moving a node upward.
MinHeap* PercolateUp(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Restore the min-heap property by moving a node downward.
MinHeap* PercolateDown(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Insert one vertex into the heap.
MinHeap* Insert(Node* nodes,MinHeap* minHeap,int Nv,int node);

// Delete one vertex from the heap by its heap index.
MinHeap* Delete(Node* nodes,MinHeap* minHeap,int Nv,int index);

// Check whether one permutation is a valid Dijkstra sequence.
bool IsDijkstraSequence(Node* nodes,MinHeap* minHeap,int Nv);

int main(){
    int Nv, Ne;                 // Number of vertices and edges
    scanf("%d %d",&Nv,&Ne);     // Read graph size
    if(Nv>Max_Nv || Nv<1 || Ne>Max_Ne || Ne<1){
        printf("Invalid input\n");
        return 0;
    }

    // Allocate the vertex array; index 1..Nv is used directly.
    Node* nodes=(Node*)malloc(sizeof(Node)*(Nv+1));
    if(nodes==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }

    // Read all edges and build the adjacency lists.
    nodes=CreatEdges(nodes,Nv,Ne);
    if(nodes==NULL)return 0;

    // The min-heap stores the current Dijkstra frontier.
    MinHeap* minHeap=(MinHeap*)malloc(sizeof(MinHeap));
    if(minHeap==NULL){
        printf("Memory allocation failed\n");
        FreeNodes(nodes,Nv);
        return 0;
    }
    minHeap->size=0;
    minHeap->indexes=(int*)malloc(sizeof(int)*(Nv+1));
    if(minHeap->indexes==NULL){
        printf("Memory allocation failed\n");
        FreeNodes(nodes,Nv);
        free(minHeap);
        return 0;
    }

    int K;                      // Number of query sequences
    scanf("%d",&K);
    if(K>Max_K || K<1){
        printf("Invalid input\n");
        FreeNodes(nodes,Nv);
        free(minHeap->indexes);
        free(minHeap);
        return 0;
    }

    // Check every query sequence independently.
    for(int i=0;i<K;i++){
        Initial(nodes,minHeap,Nv);
        if(IsDijkstraSequence(nodes,minHeap,Nv)){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }

    // Release all allocated memory before exiting.
    FreeNodes(nodes,Nv);
    if(minHeap->indexes==NULL){
        printf("Memory allocation failed\n");
        free(minHeap);
        return 0;
    }
    free(minHeap->indexes);
    free(minHeap);
    return 0;
}

Node* CreatEdges(Node* nodes,int Nv,int Ne){
    int a,b,cost;  // Edge endpoints and weight

    // Clear the vertex array so every field starts from a known state.
    memset(nodes,0,sizeof(Node)*(Nv+1));

    // Create a dummy head node for each adjacency list.
    for(int i=1;i<=Nv;i++){
        nodes[i].edges=(Edge*)malloc(sizeof(Edge));
        if(nodes[i].edges==NULL){
            printf("Memory allocation failed\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        nodes[i].edges->next=NULL;
    }

    // Read each undirected edge and append it to both endpoints.
    for(int i=1;i<=Ne;i++){
        int temp=scanf("%d %d %d",&a,&b,&cost);
        if(a>Nv || a<1 || b>Nv || b<1 || cost<0 || cost>Max_Cost || temp!=3){
            printf("Invalid input\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }

        // Store a -> b.
        Edge* a_NewEdge=(Edge*)malloc(sizeof(Edge));
        if(a_NewEdge==NULL){
            printf("Memory allocation failed\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        a_NewEdge->data=b;
        a_NewEdge->cost=cost;
        a_NewEdge->next=NULL;

        // Store b -> a.
        Edge* b_NewEdge=(Edge*)malloc(sizeof(Edge));
        if(b_NewEdge==NULL){
            printf("Memory allocation failed\n");
            FreeNodes(nodes,Nv);
            return NULL;
        }
        b_NewEdge->data=a;
        b_NewEdge->cost=cost;
        b_NewEdge->next=NULL;

        // Append the new edge to vertex a.
        Edge* current=nodes[a].edges;
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=a_NewEdge;

        // Append the reverse edge to vertex b.
        current=nodes[b].edges;
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=b_NewEdge;
    }
    return nodes;
}

Node* FreeNodes(Node* nodes,int Nv){
    // Free every adjacency list, including the dummy head node.
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
    // Reset every vertex to its initial Dijkstra state.
    for(int i=1;i<=Nv;i++){
        nodes[i].distance=Max_Cost*Max_Nv+1; // Safe infinity value
        nodes[i].before=0;
        nodes[i].index=0;
        nodes[i].visited=false;
    }
    memset(MinHeap->indexes,0,sizeof(int)*(Nv+1));
    MinHeap->size=0;
    return nodes;
}

MinHeap* PercolateUp(Node* nodes,MinHeap* minHeap,int Nv,int index){
    int parent=index/2;
    // Swap upward until the parent is no larger than the current node.
    if(parent>=1 && nodes[minHeap->indexes[index]].distance<nodes[minHeap->indexes[parent]].distance){
        int temp=minHeap->indexes[index];
        minHeap->indexes[index]=minHeap->indexes[parent];
        minHeap->indexes[parent]=temp;
        nodes[minHeap->indexes[index]].index=index;
        nodes[minHeap->indexes[parent]].index=parent;
        return PercolateUp(nodes,minHeap,Nv,parent);
    }
    return minHeap;
}

MinHeap* PercolateDown(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Stop when the current node has no child.
    if(index*2>minHeap->size)return minHeap;

    // Handle the one-child case separately.
    if(index*2+1>minHeap->size){
        if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[index*2]].distance){
            int temp=minHeap->indexes[index];
            minHeap->indexes[index]=minHeap->indexes[index*2];
            minHeap->indexes[index*2]=temp;
            nodes[minHeap->indexes[index]].index=index;
            nodes[minHeap->indexes[index*2]].index=index*2;
            return PercolateDown(nodes,minHeap,Nv,index*2);
        }
        return minHeap;
    }

    // Pick the smaller child and swap downward if necessary.
    int left=index*2;
    int right=index*2+1;
    int min;
    if(nodes[minHeap->indexes[left]].distance<=nodes[minHeap->indexes[right]].distance){
        min=left;
    }else{
        min=right;
    }
    if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[min]].distance){
        int temp=minHeap->indexes[index];
        minHeap->indexes[index]=minHeap->indexes[min];
        minHeap->indexes[min]=temp;
        nodes[minHeap->indexes[index]].index=index;
        nodes[minHeap->indexes[min]].index=min;
        return PercolateDown(nodes,minHeap,Nv,min);
    }
    return minHeap;
}

MinHeap* Insert(Node* nodes,MinHeap* minHeap,int Nv,int node){
    // Append the new vertex at the end and bubble it upward.
    minHeap->size++;
    minHeap->indexes[minHeap->size]=node;
    nodes[node].index=minHeap->size;
    return PercolateUp(nodes,minHeap,Nv,minHeap->size);
}

MinHeap* Delete(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Move the last heap element into the deleted slot, then restore order.
    minHeap->indexes[index]=minHeap->indexes[minHeap->size];
    nodes[minHeap->indexes[index]].index=index;
    minHeap->size--;
    PercolateDown(nodes,minHeap,Nv,index);
    minHeap->indexes[minHeap->size+1]=0;
    return minHeap;
}

bool IsDijkstraSequence(Node* nodes,MinHeap* minHeap,int Nv){
    int source;
    scanf("%d",&source);

    // The first vertex in the sequence is the source.
    nodes[source].distance=0;
    nodes[source].visited=true;

    // Initialize the frontier with the source's adjacent vertices.
    Edge* current=nodes[source].edges->next;
    while(current!=NULL){
        nodes[current->data].distance=current->cost;
        nodes[current->data].before=source;
        nodes[current->data].visited=true;
        Insert(nodes,minHeap,Nv,current->data);
        current=current->next;
    }

    // Validate the remaining vertices against the expected Dijkstra order.
    for(int i=2;i<=Nv;i++){
        int num;
        scanf("%d",&num);

        // The next vertex must have the same distance as the heap minimum.
        if(nodes[num].distance>nodes[minHeap->indexes[1]].distance){
            // Consume the rest of the query to keep input aligned.
            for(i=i+1;i<=Nv;i++){
                scanf("%d",&num);
            }
            return false;
        }
        else{
            Delete(nodes,minHeap,Nv,nodes[num].index);
        }

        // Relax every edge out of the selected vertex.
        current=nodes[num].edges->next;
        while(current!=NULL){
            if(nodes[current->data].visited==false){
                nodes[current->data].visited=true;
                nodes[current->data].distance=nodes[num].distance+current->cost;
                nodes[current->data].before=num;
                Insert(nodes,minHeap,Nv,current->data);
            }
            else if(nodes[current->data].distance>nodes[num].distance+current->cost){
                nodes[current->data].distance=nodes[num].distance+current->cost;
                nodes[current->data].before=num;
                PercolateUp(nodes,minHeap,Nv,current->data);
            }
            current=current->next;
        }
    }
    return true;
}