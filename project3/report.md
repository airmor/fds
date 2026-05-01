# Title of Project

Dijkstra Sequence Check (Project 3)

# Author's Name

[Hidden for peer review]

# Date

2026-05-01

## Chapter 1: Introduction

### 1.1 Problem Description

Dijkstra's algorithm generates a sequence of vertices by repeatedly selecting an undiscovered vertex with the minimum tentative distance from the source. For a given weighted, connected, undirected graph, multiple valid Dijkstra sequences may exist because of ties. This project checks whether each given permutation of vertices can be produced by Dijkstra's algorithm when the first vertex in the permutation is treated as the source.

### 1.2 Input and Output Summary

Input:
- Nv and Ne
- Ne undirected weighted edges
- K sequences, each a permutation of 1..Nv

Output:
- For each sequence, print Yes if it is a valid Dijkstra sequence, otherwise print No.

## Chapter 2: Algorithm Specification

### 2.1 Main Data Structures

```c
// Use int as a simple boolean type.
#define bool int
// Define the true literal as 1.
#define true 1
// Define the false literal as 0.
#define false 0

// Maximum number of vertices allowed by the problem.
#define Max_Nv 1000
// Maximum number of edges allowed by the problem.
#define Max_Ne 100000
// Maximum number of query sequences allowed by the problem.
#define Max_K 100
// Maximum edge weight allowed by the problem.
#define Max_Cost 100

// Vertex record used by the graph and the heap.
typedef struct Node Node;
// Edge record used by the adjacency lists.
typedef struct Edge Edge;
// Heap record used to track candidate vertices.
typedef struct MinHeap MinHeap;

// Each vertex stores the current tentative distance, visit state,
// predecessor, heap position, and adjacency-list head pointer.
struct Node{
    int distance;   // Current shortest distance estimate.
    bool visited;   // Whether this vertex has been discovered.
    int before;     // Previous vertex on the current shortest path.
    int index;      // Current heap position of this vertex.
    Edge* edges;    // Head of the adjacency list.
};

// Each edge stores the destination vertex, its cost, and the next edge.
struct Edge{
    int data;          // Adjacent vertex id.
    int cost;          // Edge weight.
    struct Edge* next;  // Next edge in the adjacency list.
};

// Min-heap of vertex ids used to simulate Dijkstra's frontier.
struct MinHeap{
    int size;      // Number of valid elements currently in the heap.
    int* indexes;  // Vertex ids arranged according to heap order.
};
```

- The graph is stored as adjacency lists without dummy head nodes.
- A min-heap stores the frontier vertices ordered by tentative distance.

### 2.2 Algorithm Pseudo-code

#### Algorithm 0: Main Procedure

```text
MAIN():
    read Nv, Ne
    if Nv or Ne out of range:
        print "Invalid input"
        exit

    nodes = allocate Node[Nv + 1]
    if nodes == NULL:
        print "Memory allocation failed"
        exit

    nodes = BUILD_GRAPH(Nv, Ne)
    if nodes == NULL:
        exit

    minHeap = allocate MinHeap
    if minHeap == NULL:
        print "Memory allocation failed"
        free nodes
        exit

    minHeap.indexes = allocate int[Nv + 1]
    if minHeap.indexes == NULL:
        print "Memory allocation failed"
        free nodes and minHeap
        exit

    read K
    if K out of range:
        print "Invalid input"
        free nodes and minHeap
        exit

    for each query in 1..K:
        INITIALIZE(Nv)
        if CHECK_SEQUENCE(query) is true:
            print "Yes"
        else:
            print "No"

    FREE_NODES(nodes)
    free minHeap.indexes and minHeap
    exit
```

#### Algorithm A: Build Graph (CreatEdges)

```text
BUILD_GRAPH(Nv, Ne):
    initialize nodes[1..Nv]
    for v = 1..Nv:
        nodes[v].edges = NULL

    repeat Ne times:
        read (u, v, w)
        create edge e1 = (u -> v, cost w)
        create edge e2 = (v -> u, cost w)

        // head insert e1 into u's list
        e1.next = nodes[u].edges
        nodes[u].edges = e1

        // head insert e2 into v's list
        e2.next = nodes[v].edges
        nodes[v].edges = e2

    return nodes
```

#### Algorithm B: Initialize One Query (Initial)

```text
INITIALIZE(Nv):
    for v = 1..Nv:
        distance[v] = INF
        before[v] = 0
        index[v] = 0
        visited[v] = false
    heap.size = 0
    clear heap.indexes[1..Nv]
```

#### Algorithm C: Heap Operations

```text
PERCOLATE_UP(i):
    while i > 1:
        p = i / 2
        if dist[heap[i]] < dist[heap[p]]:
            swap(heap[i], heap[p])
            update index for both vertices
            i = p
        else:
            break

PERCOLATE_DOWN(i):
    while i * 2 <= heap.size:
        left = i * 2
        right = i * 2 + 1
        if right <= heap.size and dist[heap[right]] < dist[heap[left]]:
            child = right
        else:
            child = left
        if dist[heap[child]] < dist[heap[i]]:
            swap(heap[i], heap[child])
            update index for both vertices
            i = child
        else:
            break

INSERT(v):
    heap.size = heap.size + 1
    heap[heap.size] = v
    index[v] = heap.size
    PERCOLATE_UP(heap.size)

DELETE_BY_INDEX(i):
    heap[i] = heap[heap.size]
    index[heap[i]] = i
    heap.size = heap.size - 1
    PERCOLATE_DOWN(i)
```

#### Algorithm D: Check One Sequence (IsDijkstraSequence)

```text
CHECK_SEQUENCE(seq[1..Nv]):
    source = seq[1]
    distance[source] = 0
    visited[source] = true

    // push neighbors of source
    for each edge (source -> x, cost c):
        distance[x] = c
        before[x] = source
        visited[x] = true
        INSERT(x)

    for i = 2..Nv:
        v = seq[i]
        if distance[v] > distance[heap[1]]:
            consume remaining input in this sequence
            return false
        DELETE_BY_INDEX(index[v])

        for each edge (v -> x, cost c):
            if visited[x] == false:
                visited[x] = true
                distance[x] = distance[v] + c
                before[x] = v
                INSERT(x)
            else if distance[x] > distance[v] + c:
                distance[x] = distance[v] + c
                before[x] = v
                PERCOLATE_UP(index[x])

    return true
```

## Chapter 3: Testing Results

Full inputs and outputs are listed in test.md. The table below summarizes the results for 12 cases, including decrease-key scenarios.

| Case ID | Purpose | Input | Expected Result | Actual Behavior | Possible Cause of Bug (if failed) | Status |
|---|---|---|---|---|---|---|
| TC-01 | Official sample; verify output matches the problem statement | 5 7<br>1 2 2<br>1 5 1<br>2 3 1<br>2 4 1<br>2 5 2<br>3 5 1<br>3 4 1<br>4<br>5 1 3 4 2<br>5 3 1 2 4<br>2 3 4 5 1<br>3 2 1 5 4 | Yes<br>Yes<br>Yes<br>No | Yes<br>Yes<br>Yes<br>No | - | pass |
| TC-02 | Equal shortest paths; different valid tie orders | 4 4<br>1 2 1<br>1 3 1<br>2 4 1<br>3 4 1<br>4<br>1 2 3 4<br>1 3 2 4<br>1 4 2 3<br>1 2 4 3 | Yes<br>Yes<br>No<br>No | Yes<br>Yes<br>No<br>No | - | pass |
| TC-03 | Chain graph; only increasing distance order is valid | 4 3<br>1 2 2<br>2 3 2<br>3 4 2<br>3<br>1 2 3 4<br>1 3 2 4<br>1 2 4 3 | Yes<br>No<br>No | Yes<br>No<br>No | - | pass |
| TC-04 | Minimum graph size | 2 1<br>1 2 5<br>2<br>1 2<br>2 1 | Yes<br>Yes | Yes<br>Yes | - | pass |
| TC-05 | Max edge weight boundary (w = 100) | 2 1<br>1 2 100<br>2<br>1 2<br>2 1 | Yes<br>Yes | Yes<br>Yes | - | pass |
| TC-06 | Complete graph; all permutations should be valid | 3 3<br>1 2 1<br>1 3 1<br>2 3 1<br>3<br>1 2 3<br>1 3 2<br>2 1 3 | Yes<br>Yes<br>Yes | Yes<br>Yes<br>Yes | - | pass |
| TC-07 | Star graph; leaf order is flexible | 4 3<br>1 2 2<br>1 3 2<br>1 4 2<br>2<br>1 2 3 4<br>1 4 3 2 | Yes<br>Yes | Yes<br>Yes | - | pass |
| TC-08 | Multiple equal-length branches | 5 6<br>1 2 1<br>1 3 1<br>2 4 1<br>3 4 1<br>2 5 2<br>3 5 2<br>3<br>1 2 3 4 5<br>1 3 2 4 5<br>1 2 4 3 5 | Yes<br>Yes<br>No | Yes<br>Yes<br>No | - | pass |
| TC-09 | Large weight gap | 3 2<br>1 2 100<br>2 3 1<br>2<br>1 2 3<br>1 3 2 | Yes<br>No | Yes<br>No | - | pass |
| TC-10 | Cycle graph | 4 4<br>1 2 1<br>2 3 1<br>3 4 1<br>4 1 1<br>3<br>1 2 3 4<br>1 4 3 2<br>1 2 4 3 | No<br>No<br>Yes | No<br>No<br>Yes | - | pass |
| TC-11 | Decrease-key; shorter path discovered after insertion | 3 3<br>1 2 10<br>1 3 1<br>3 2 1<br>2<br>1 3 2<br>1 2 3 | Yes<br>No | Yes<br>No | - | pass |
| TC-12 | Decrease-key in branching paths | 4 5<br>1 2 5<br>1 3 1<br>3 2 1<br>2 4 1<br>3 4 10<br>2<br>1 3 2 4<br>1 2 3 4 | Yes<br>No | Yes<br>No | - | pass |

## Chapter 4: Analysis and Comments

### 4.1 Time Complexity

The analysis below uses Nv for the number of vertices, Ne for the number of edges, and K for the number of sequences.

- main: input reading and dispatching is O(Nv + Ne + K * Nv) plus the costs of called functions.
- CreatEdges: initialize adjacency heads in O(Nv), then perform two O(1) head inserts per edge, so total O(Nv + Ne).
- FreeNodes: visit and free each adjacency node once, O(Nv + Ne).
- Initial: reset all vertices and heap slots, O(Nv).
- PercolateUp / PercolateDown: each heap fix is O(log Nv).
- Insert / Delete: O(log Nv) per operation.
- IsDijkstraSequence: read the sequence in O(Nv). Each edge is relaxed at most once; each relax triggers at most one heap operation, so O(Ne log Nv). Total per sequence is O((Nv + Ne) log Nv).

Total time complexity (current implementation):
- O(Nv + Ne + K * (Nv + Ne) log Nv).

### 4.2 Space Complexity

- Vertex array: O(Nv) for Node records.
- Edge storage: O(Ne), storing 2 * Ne adjacency nodes for an undirected graph.
- Heap storage: O(Nv) for the indexes array, plus O(1) for the MinHeap struct.
- Extra variables and call stack: O(1) (no recursion).

Total space complexity: O(Nv + Ne).

### 4.3 Comments and Possible Improvements

1. The checker is correct in principle: each selected vertex must match the current minimum tentative distance, so tie cases are handled naturally.
2. The adjacency list uses head insertion without dummy nodes, making graph construction O(Nv + Ne) and simpler in memory layout.
3. Decrease-key is handled by heap index percolation, which is essential to keep heap order valid after distance updates.
4. Further code-level improvements: validate each query as a full permutation of 1..Nv, use a safer INF sentinel (for example INT_MAX / 4), and replace recursive heap percolation with iterative loops.

## Appendix: Source Code (in C)

To keep the report and implementation fully synchronized, the canonical source code is maintained in the repository file below:

- project3/code/main.c

This report's data structure description, pseudocode, and complexity analysis are all aligned with that file's current implementation (no dummy head nodes, adjacency-list head insertion).

```c
// Include stdio for scanf and printf.
#include <stdio.h>
// Include stdlib for malloc and free.
#include <stdlib.h>
// Include string.h for memset.
#include <string.h>

// Use int as a simple boolean type.
#define bool int
// Define the true literal as 1.
#define true 1
// Define the false literal as 0.
#define false 0

// Maximum number of vertices allowed by the problem.
#define Max_Nv 1000
// Maximum number of edges allowed by the problem.
#define Max_Ne 100000
// Maximum number of query sequences allowed by the problem.
#define Max_K 100
// Maximum edge weight allowed by the problem.
#define Max_Cost 100

// Vertex record used by the graph and the heap.
typedef struct Node Node;
// Edge record used by the adjacency lists.
typedef struct Edge Edge;
// Heap record used to track candidate vertices.
typedef struct MinHeap MinHeap;

// Each vertex stores the current tentative distance, visit state,
// predecessor, heap position, and adjacency-list head.
struct Node{
    int distance;   // Current shortest distance estimate.
    bool visited;   // Whether this vertex has been discovered.
    int before;     // Previous vertex on the current shortest path.
    int index;      // Current heap position of this vertex.
    Edge* edges;    // Head of the adjacency list.
};

// Each edge stores the destination vertex, its cost, and the next edge.
struct Edge{
    int data;          // Adjacent vertex id.
    int cost;          // Edge weight.
    struct Edge* next;  // Next edge in the adjacency list.
};

// Min-heap of vertex ids used to simulate Dijkstra's frontier.
struct MinHeap{
    int size;      // Number of valid elements currently in the heap.
    int* indexes;  // Vertex ids arranged according to heap order.
};



// Build all edges and link them into adjacency lists.
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
    int Nv, Ne;                                             // Number of vertices and edges.
    scanf("%d %d",&Nv,&Ne);                                // Read graph size.
    if(Nv>Max_Nv || Nv<1 || Ne>Max_Ne || Ne<1){             // Validate graph size.
        printf("Invalid input\n");                         // Reject out-of-range graph data.
        return 0;                                           // Exit immediately on invalid input.
    }

    // Allocate the vertex array; index 1..Nv is used directly.
    Node* nodes=(Node*)malloc(sizeof(Node)*(Nv+1));         // Allocate storage for all vertices.
    if(nodes==NULL){                                        // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        return 0;                                           // Stop because the graph cannot be built.
    }

    // Read all edges and build the adjacency lists.
    nodes=CreatEdges(nodes,Nv,Ne);                          // Build the graph from input.
    if(nodes==NULL)return 0;                                // Abort if graph construction failed.

    // The min-heap stores the current Dijkstra frontier.
    MinHeap* minHeap=(MinHeap*)malloc(sizeof(MinHeap));     // Allocate the heap container.
    if(minHeap==NULL){                                      // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        return 0;                                           // Stop because the heap cannot be built.
    }
    minHeap->size=0;                                        // Start with an empty heap.
    minHeap->indexes=(int*)malloc(sizeof(int)*(Nv+1));      // Allocate heap storage.
    if(minHeap->indexes==NULL){                             // Check whether allocation succeeded.
        printf("Memory allocation failed\n");              // Report allocation failure.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Stop because the heap array cannot be built.
    }

    int K;                                                  // Number of query sequences.
    scanf("%d",&K);                                         // Read the number of queries.
    if(K>Max_K || K<1){                                     // Validate query count.
        printf("Invalid input\n");                         // Reject out-of-range query count.
        FreeNodes(nodes,Nv);                                // Release graph memory before exiting.
        free(minHeap->indexes);                             // Release heap storage.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Stop because the query count is invalid.
    }

    // Check every query sequence independently.
    for(int i=0;i<K;i++){                                   // Process each query sequence once.
        Initial(nodes,minHeap,Nv);                          // Reset all vertex and heap state.
        if(IsDijkstraSequence(nodes,minHeap,Nv)){           // Test whether the sequence is valid.
            printf("Yes\n");                                // Print success for a valid sequence.
        }
        else{                                               // The sequence failed the Dijkstra check.
            printf("No\n");                                 // Print failure for an invalid sequence.
        }
    }

    // Release all allocated memory before exiting.
    FreeNodes(nodes,Nv);                                    // Free the graph structure.
    if(minHeap->indexes==NULL){                             // Preserve the original cleanup branch.
        printf("Memory allocation failed\n");              // Report a memory failure message.
        free(minHeap);                                      // Release the heap container.
        return 0;                                           // Exit on failure.
    }
    free(minHeap->indexes);                                 // Release the heap array.
    free(minHeap);                                          // Release the heap container.
    return 0;                                               // Normal exit.
}

Node* CreatEdges(Node* nodes,int Nv,int Ne){
    int a,b,cost;                                           // Edge endpoints and weight.

    // Clear the vertex array so every field starts from a known state.
    memset(nodes,0,sizeof(Node)*(Nv+1));                    // Initialize all vertex records to zero.

    // Initialize each adjacency list head to NULL.
    for(int i=1;i<=Nv;i++){                                 // Visit every vertex once.
        nodes[i].edges=NULL;                                // No edges yet.
    }

    // Read each undirected edge and insert it into both endpoints.
    for(int i=1;i<=Ne;i++){                                 // Process every input edge.
        int temp=scanf("%d %d %d",&a,&b,&cost);            // Read one edge record.
        if(a>Nv || a<1 || b>Nv || b<1 || cost<0 || cost>Max_Cost || temp!=3){ // Validate the edge record.
            printf("Invalid input\n");                     // Reject malformed edge data.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }

        // Store a -> b.
        Edge* a_NewEdge=(Edge*)malloc(sizeof(Edge));        // Allocate the forward adjacency node.
        if(a_NewEdge==NULL){                                // Check whether allocation succeeded.
            printf("Memory allocation failed\n");          // Report allocation failure.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }
        a_NewEdge->data=b;                                  // Store the destination vertex.
        a_NewEdge->cost=cost;                               // Store the edge weight.
        a_NewEdge->next=NULL;                               // This node is currently the tail.

        // Store b -> a.
        Edge* b_NewEdge=(Edge*)malloc(sizeof(Edge));        // Allocate the reverse adjacency node.
        if(b_NewEdge==NULL){                                // Check whether allocation succeeded.
            printf("Memory allocation failed\n");          // Report allocation failure.
            FreeNodes(nodes,Nv);                            // Free all partially built graph data.
            return NULL;                                    // Signal failure to the caller.
        }
        b_NewEdge->data=a;                                  // Store the destination vertex.
        b_NewEdge->cost=cost;                               // Store the edge weight.
        b_NewEdge->next=NULL;                               // This node is currently the tail.

        // Insert the new edge at the head of vertex a.
        a_NewEdge->next=nodes[a].edges;                     // Point to the current head edge.
        nodes[a].edges=a_NewEdge;                           // Link the new forward edge at the head.

        // Insert the reverse edge at the head of vertex b.
        b_NewEdge->next=nodes[b].edges;                     // Point to the current head edge.
        nodes[b].edges=b_NewEdge;                           // Link the new reverse edge at the head.
    }
    return nodes;                                           // Return the fully built graph.
}

Node* FreeNodes(Node* nodes,int Nv){
    // Free every adjacency list.
    for(int i=1;i<=Nv;i++){                                 // Visit each vertex in order.
        Edge* current=nodes[i].edges;                       // Start from the head of the adjacency list.
        while(current!=NULL){                               // Traverse the whole list.
            Edge* temp=current;                             // Save the current node before freeing it.
            current=current->next;                          // Advance to the next node.
            free(temp);                                     // Release the current edge node.
        }
    }
    free(nodes);                                            // Release the vertex array itself.
    return NULL;                                            // Return NULL for convenient cleanup assignment.
}

Node* Initial(Node* nodes,MinHeap* MinHeap,int Nv){
    // Reset every vertex to its initial Dijkstra state.
    for(int i=1;i<=Nv;i++){                                 // Visit each vertex once.
        nodes[i].distance=Max_Cost*Max_Nv+1;               // Set distance to a safe infinity value.
        nodes[i].before=0;                                 // Clear predecessor information.
        nodes[i].index=0;                                  // Clear heap position information.
        nodes[i].visited=false;                            // Mark the vertex as undiscovered.
    }
    memset(MinHeap->indexes,0,sizeof(int)*(Nv+1));         // Clear all heap slots.
    MinHeap->size=0;                                       // Reset heap size to zero.
    return nodes;                                          // Return the reset vertex array.
}

MinHeap* PercolateUp(Node* nodes,MinHeap* minHeap,int Nv,int index){
    int parent=index/2;                                    // Compute the parent index.
    // Swap upward until the parent is no larger than the current node.
    if(parent>=1 && nodes[minHeap->indexes[index]].distance<nodes[minHeap->indexes[parent]].distance){ // Compare child and parent distances.
        int temp=minHeap->indexes[index];                  // Save the current vertex id.
        minHeap->indexes[index]=minHeap->indexes[parent];  // Move the parent down.
        minHeap->indexes[parent]=temp;                     // Move the current vertex up.
        nodes[minHeap->indexes[index]].index=index;        // Update the moved vertex's heap position.
        nodes[minHeap->indexes[parent]].index=parent;      // Update the other moved vertex's heap position.
        return PercolateUp(nodes,minHeap,Nv,parent);       // Continue bubbling upward.
    }
    return minHeap;                                        // Heap order is already correct.
}

MinHeap* PercolateDown(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Stop when the current node has no child.
    if(index*2>minHeap->size)return minHeap;               // No children means the heap order is satisfied.

    // Handle the one-child case separately.
    if(index*2+1>minHeap->size){                           // Only a left child exists.
        if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[index*2]].distance){ // Compare parent and left child.
            int temp=minHeap->indexes[index];              // Save the current vertex id.
            minHeap->indexes[index]=minHeap->indexes[index*2]; // Move the left child up.
            minHeap->indexes[index*2]=temp;                // Move the parent down.
            nodes[minHeap->indexes[index]].index=index;    // Update the moved vertex's heap position.
            nodes[minHeap->indexes[index*2]].index=index*2; // Update the other moved vertex's heap position.
            return PercolateDown(nodes,minHeap,Nv,index*2); // Continue bubbling downward.
        }
        return minHeap;                                    // Heap order is already correct.
    }

    // Pick the smaller child and swap downward if necessary.
    int left=index*2;                                      // Left child index.
    int right=index*2+1;                                   // Right child index.
    int min;                                               // Index of the smaller child.
    if(nodes[minHeap->indexes[left]].distance<=nodes[minHeap->indexes[right]].distance){ // Compare child distances.
        min=left;                                          // Left child is smaller or equal.
    }else{
        min=right;                                         // Right child is smaller.
    }
    if(nodes[minHeap->indexes[index]].distance>nodes[minHeap->indexes[min]].distance){ // Compare parent and smaller child.
        int temp=minHeap->indexes[index];                  // Save the current vertex id.
        minHeap->indexes[index]=minHeap->indexes[min];     // Move the smaller child up.
        minHeap->indexes[min]=temp;                        // Move the parent down.
        nodes[minHeap->indexes[index]].index=index;        // Update the moved vertex's heap position.
        nodes[minHeap->indexes[min]].index=min;            // Update the other moved vertex's heap position.
        return PercolateDown(nodes,minHeap,Nv,min);        // Continue bubbling downward.
    }
    return minHeap;                                        // Heap order is already correct.
}

MinHeap* Insert(Node* nodes,MinHeap* minHeap,int Nv,int node){
    // Append the new vertex at the end and bubble it upward.
    minHeap->size++;                                       // Increase heap size first.
    minHeap->indexes[minHeap->size]=node;                  // Place the new vertex at the tail.
    nodes[node].index=minHeap->size;                       // Record the heap position in the vertex.
    return PercolateUp(nodes,minHeap,Nv,minHeap->size);    // Restore heap order from the new slot.
}

MinHeap* Delete(Node* nodes,MinHeap* minHeap,int Nv,int index){
    // Move the last heap element into the deleted slot, then restore order.
    minHeap->indexes[index]=minHeap->indexes[minHeap->size]; // Copy the last heap element into the gap.
    nodes[minHeap->indexes[index]].index=index;             // Update the moved vertex's heap position.
    minHeap->size--;                                        // Shrink the heap.
    PercolateDown(nodes,minHeap,Nv,index);                  // Restore order from the affected slot.
    minHeap->indexes[minHeap->size+1]=0;                    // Clear the stale tail slot.
    return minHeap;                                         // Return the updated heap.
}

bool IsDijkstraSequence(Node* nodes,MinHeap* minHeap,int Nv){
    int source;                                             // Source vertex from the query sequence.
    scanf("%d",&source);                                    // Read the source vertex.

    // The first vertex in the sequence is the source.
    nodes[source].distance=0;                               // The source distance is zero.
    nodes[source].visited=true;                              // Mark the source as discovered.

    // Initialize the frontier with the source's adjacent vertices.
    Edge* current=nodes[source].edges;                       // Start from the adjacency list head.
    while(current!=NULL){                                    // Traverse all neighbors of the source.
        nodes[current->data].distance=current->cost;         // Set the initial tentative distance.
        nodes[current->data].before=source;                  // Set the source as predecessor.
        nodes[current->data].visited=true;                   // Mark the neighbor as discovered.
        Insert(nodes,minHeap,Nv,current->data);              // Insert the neighbor into the heap.
        current=current->next;                               // Move to the next neighbor.
    }

    // Validate the remaining vertices against the expected Dijkstra order.
    for(int i=2;i<=Nv;i++){                                  // Check the remaining vertices one by one.
        int num;                                             // Vertex id read from the query sequence.
        scanf("%d",&num);                                    // Read the next vertex in the sequence.

        // The next vertex must have the same distance as the heap minimum.
        if(nodes[num].distance>nodes[minHeap->indexes[1]].distance){ // Compare against the current minimum.
            // Consume the rest of the query to keep input aligned.
            for(i=i+1;i<=Nv;i++){                            // Skip the remaining vertex ids.
                scanf("%d",&num);                           // Read and discard one vertex id.
            }
            return false;                                    // The sequence is not a valid Dijkstra order.
        }
        else{                                                // The chosen vertex matches the heap minimum distance.
            Delete(nodes,minHeap,Nv,nodes[num].index);       // Remove it from the heap.
        }

        // Relax every edge out of the selected vertex.
        current=nodes[num].edges;                            // Start from the adjacency list head.
        while(current!=NULL){                                // Traverse all neighbors of the selected vertex.
            if(nodes[current->data].visited==false){         // First time discovering this vertex.
                nodes[current->data].visited=true;           // Mark it as discovered.
                nodes[current->data].distance=nodes[num].distance+current->cost; // Set its tentative distance.
                nodes[current->data].before=num;             // Record the predecessor.
                Insert(nodes,minHeap,Nv,current->data);      // Push it into the heap.
            }
            else if(nodes[current->data].distance>nodes[num].distance+current->cost){ // Found a shorter path.
                nodes[current->data].distance=nodes[num].distance+current->cost;     // Update the distance.
                nodes[current->data].before=num;            // Update the predecessor.
                PercolateUp(nodes,minHeap,Nv,nodes[current->data].index); // Restore heap order after the decrease.
            }
            current=current->next;                           // Move to the next adjacency node.
        }
    }
    return true;                                             // The sequence satisfies Dijkstra's rule.
}
```

## Declaration

I hereby declare that all the work done in this project titled "Dijkstra Sequence Check (Project 3)" is of my independent effort.
